//
// Created by cyril on 16/05/2022.
//

#include "Client.h"
#include "../System/Random.h"
#include "Lobby.h"
#include <chrono>

Client::Client(std::string name) : udpSocket_(name), lobbyList_(SERVER_NB_MAX_LOBBY), ping_(50) {
    name_ = name;
    clientSeed_ = Random::rand();
    challengeResponse_ = 0;
    udpSocket_.setVerbose(false);
    udpSocket_.setBlocking(false);
    udpSocket_.bind(sf::Socket::AnyPort);
    playerIndex_ = 0;
    pingIndex_ = 0;

    for (int i = 0; i < ping_.size(); i++) {
        ping_[i] = -1;
    }

    for (int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
        for (int j = 0; j < NB_MAX_JOUEURS; j++) {
            lobbyList_[i].players[j] = new PlayerInfo();
        }
    }
}

Client::~Client()
{
    for (int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
        for (int j = 0; j < NB_MAX_JOUEURS; j++) {
            delete lobbyList_[i].players[j];
        }
    }
}

std::string Client::getLobbyIndex()
{
    return lobbyIndex_;
}

Lobby& Client::getCurrentLobby()
{
    return lobbyList_[lobbyInd_];
}


Lobby& Client::getLobby(int i)
{
    return lobbyList_[i];
}

int Client::getPlayerIndex()
{
    return playerIndex_;
}

float Client::getServerBeat()
{
    return serverBeat_;
}

sf::Int64 Client::getPing()
{
    float res = 0;
    int nb = 0;
    for (int i = 0; i < ping_.size(); i++) {
        if (ping_[i] != -1) {
            nb++;
            res += ping_[i];
        }
    }
    return res/(float)nb;
}

void Client::changeName(const std::string& name)
{
    name_ = name;
}

sf::Socket::Status receiveWithTimeout(sf::TcpSocket& socket, sf::Packet& packet, sf::Time timeout)
{
    sf::SocketSelector selector;
    selector.add(socket);
    if (selector.wait(timeout))
        return socket.receive(packet);
    else
        return sf::Socket::NotReady;
}

bool Client::connectToServer() {
    sf::Socket::Status status;


    status = tcpSocket_.connect(SERVER_IP, SERVER_CONNECT_PORT, sf::seconds(5));

    if (status != sf::Socket::Done) {
        std::cout << "connectToServer : Unable to reach the server" << std::endl;
        return false;
    }

    sf::Packet p;
    sf::Uint8 state = 100, rep = 1;
    sf::Int32 serverSeed;
    sf::Uint16 port = udpSocket_.getPort();


    p << state << sf::String(name_) << clientSeed_ << port;
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "connectToServer : Unable to reach the server (send 100)" << std::endl;
        return false;
    }


    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    if (status == sf::Socket::NotReady) {
        std::cout << "connectToServer : Time out" << std::endl;
        return false;
    }

    if (status != sf::Socket::Done) {
        std::cout << "connectToServer : Unable to reach the server (recieve)" << std::endl;
        return false;
    }

    p >> state;
    if (!p) {
        std::cout << "connectToServer : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 100) {
        std::cout << "connectToServer : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "connectToServer : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "connectToServer : Player limit reached." << std::endl;
        return false;
    }

    p >> serverSeed;

    if (!p) {
        std::cout << "connectToServer : Data corrupted (seed)" << std::endl;
        return false;
    }

    p.clear();

    state = 101;
    challengeResponse_ = clientSeed_ ^ serverSeed;

    p << state << challengeResponse_;

    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "connectToServer : Unable to reach the server (send 101)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "connectToServer : Data corrupted (state101)" << std::endl;
        return false;
    }

    if (state != 101) {
        std::cout << "connectToServer : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    std::cout << "Connected !" << std::endl;

    return true;
}

bool Client::disconectToServer() {

    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 110;

    p << state;
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "disconectToServer : Unable to reach the server (send)" << std::endl;
        return false;
    }

    tcpSocket_.disconnect();

    return true;

}

void Client::sendCommand(const std::string& cmd) {
    udpSocket_.setBlocking(true);
    sf::Packet packet;
    packet << cmd;
    udpSocket_.send(packet, SERVER_IP, SERVER_ADMIN_PORT);
    if(udpSocket_.recieve()) {
        std::string msg;
        udpSocket_.getRecievedPacket() >> msg;
        std::cout << msg << std::endl;
    }
    udpSocket_.setBlocking(false);
}

void Client::sendPlayerData(sf::Int32 x, sf::Int32 y) {
    sf::Packet packet;
    sf::Uint8 state = 0;
    packet << challengeResponse_ << state << packetID_ << x << y;
    udpSocket_.send(packet, SERVER_IP, SERVER_GAME_PORT);
    packetID_++;
}

int Client::updateFromServerPlayerPosition(std::vector<Joueur> &joueurs, std::pair<float, float> &checkpoint) {


    sf::Packet packet;
    sf::Socket::Status status = receiveWithTimeout(tcpSocket_, packet, sf::milliseconds(SERVER_SLEEP));

    if (status == sf::Socket::Done) {
        std::cout << "TCP_SOCKET : Packet recieved." << std::endl;

        sf::Uint8 state;
        packet >> state;

        if (!packet) {
            std::cout << "updateFromServerPlayerPosition : Can't read state." << std::endl;
            return 0;
        }

        if (state == 33) { // INTERRUPT
            return 1;
        }
        if (state == 34) { // PAUSE

            float checkpointFirst, checkpointSecond;

            packet >> checkpointFirst >> checkpointSecond;
            if (!packet) {
                std::cout << "updateFromServerPlayerPosition : Invalid packet (34)." << std::endl;
                return 0;
            }
            checkpoint.first = checkpointFirst;
            checkpoint.second = checkpointSecond;
            return 2;
        }
        if (state == 35) { // RESUME
            return 3;
        }
    }

    if (udpSocket_.recieve()) {
        sf::Uint8 state = 0;

        udpSocket_.getRecievedPacket() >> state;

        if (!udpSocket_.valid()) {
            std::cout << "GAME PORT : Data corrupted (updateFromServerPlayerPosition)." << std::endl;
            return 0;
        }

        if (state == 0) {
            for (int i = 0; i < joueurs.size(); i++) {
                joueurs[i].setDataFromServer(udpSocket_.getRecievedPacket());
            }
        }
        if (state == 1) {
            float beat;
            sf::Int64 serverTime, clientTime, clientSentTime;
            udpSocket_.getRecievedPacket() >> clientSentTime >> serverTime >> beat;

            if (!udpSocket_.valid()) {
                std::cout << "GAME PORT : Data corrupted (updateFromServerPlayerPosition - 1)." << std::endl;
                return 0;
            }

            serverBeat_ = beat;

            clientTime = std::chrono::steady_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
            offset_ = (clientTime - serverTime)/2;
            ping_[pingIndex_] = clientTime - clientSentTime;
            pingIndex_++;
            pingIndex_ = pingIndex_ % ping_.size();
            return 4;
        }
    }
        
    

    return 0;
}




bool Client::monitorLobby(int& roomState) {

    
    sf::Packet packet;
    sf::Socket::Status status = receiveWithTimeout(tcpSocket_, packet, sf::milliseconds(SERVER_SLEEP));

    if (status == sf::Socket::Done) {
        std::cout << "TCP_SOCKET : Packet recieved." << std::endl;

        sf::Uint8 state;
        packet >> state;

        if (!packet) {
            std::cout << "TCP_SOCKET : Can't read state." << std::endl;
            return false;
        }

        if (state == 30) { //Start Game
            sf::Uint8 ind;
            packet >> ind;
            index_ = ind;
            roomState = 1;
        }
        if (state == 31) { // Lobby Disband
            roomState = -1;
        }
        if (state == 32) { // Refresh Lobby Info
            roomState = 2;
        }
    }

    return true;
}



bool Client::requestLobbyList() {

    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 40;

    p << state;
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "requestLobbyList : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "requestLobbyList : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 40) {
        std::cout << "requestLobbyList : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    for (int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
        sf::Uint8 status, nbIn, limit;
        sf::String id, lobyname, playername;
       
        p >> status >> id >> lobyname >> nbIn >> limit >> playername;

        if (!p) {
            std::cout << "requestLobbyList : Data corrupted (" << i << ")" << std::endl;
            return false;
        }

        lobbyList_[i].id = id;
        lobbyList_[i].name = lobyname;
        lobbyList_[i].nbIn = nbIn;
        lobbyList_[i].limit = limit;
        lobbyList_[i].players[0]->name = playername;

        lobbyList_[i].status = static_cast<LobbyStatus>(status);
    }

    return true;
}

bool Client::requestLobbyInfo(const std::string& lobbyIndex) {

    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 41;

    p << state << lobbyIndex;
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "requestLobbyInfo : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "requestLobbyInfo : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 41) {
        std::cout << "requestLobbyInfo : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    int id = findLobbyById(lobbyList_, lobbyIndex);

    sf::Uint8 nbIn, limit, playerstatus;
    sf::Uint32 color;
    sf::String lobyname, playername, beatmap, mode;

    p >> lobyname >> nbIn >> limit >> beatmap >> mode;

    if (!p) {
        std::cout << "requestLobbyInfo : Data corrupted (header)" << std::endl;
        return false;
    }

    lobbyList_[id].name = lobyname;
    lobbyList_[id].nbIn = nbIn;
    lobbyList_[id].limit = limit;
    lobbyList_[id].beatmap = beatmap;
    lobbyList_[id].mode = mode;

    for (int i = 0; i < NB_MAX_JOUEURS; i++) {
        p >> playerstatus >> playername >> color;

        if (!p) {
            std::cout << "requestLobbyInfo : Data corrupted (" << i << ")" << std::endl;
            return false;
        }
        lobbyList_[id].players[i]->name = playername;
        lobbyList_[id].players[i]->color = color;
        lobbyList_[id].players[i]->status = (PlayerStatus)playerstatus;
    }

    return true;
}


bool Client::requestLobbyCreation(const std::string& name, const std::string& beatmap, const std::string& mode) {

    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 10, rep;

    p << state << sf::String(name) << sf::String(beatmap) << sf::String(mode);
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "requestLobbyCreation : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "requestLobbyCreation : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 10) {
        std::cout << "requestLobbyCreation : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "requestLobbyCreation : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "requestLobbyCreation : Player not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "requestLobbyCreation : Player is in wrong state." << std::endl;
        return false;
    }

    if (rep == 3) {
        std::cout << "requestLobbyCreation : Lobby limit reached." << std::endl;
        return false;
    }

    sf::String index;
    p >> index;

    if (!p) {
        std::cout << "requestLobbyCreation : Data corrupted (index)" << std::endl;
        return false;
    }

    playerIndex_ = 0;
    lobbyIndex_ = index;
    requestLobbyList();
    lobbyInd_ = findLobbyById(lobbyList_, index);

    return true;
}

bool Client::requestLobbyJoin(const std::string &lobbyIndex) {
    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 11, rep;

    lobbyIndex_ = lobbyIndex;
    lobbyInd_ = findLobbyById(lobbyList_, lobbyIndex_);

    p << state << sf::String(lobbyIndex_);
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "requestLobbyJoin : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "requestLobbyJoin : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 11) {
        std::cout << "requestLobbyJoin : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "requestLobbyJoin : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "requestLobbyJoin : Player not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "requestLobbyJoin : Lobby not found." << std::endl;
        return false;
    }

    if (rep == 3) {
        std::cout << "requestLobbyJoin : Lobby is not ready." << std::endl;
        return false;
    }

    if (rep == 4) {
        std::cout << "requestLobbyJoin : Room is full." << std::endl;
        return false;
    }

    sf::Int32 playerindex;
    p >> playerindex;

    if (!p) {
        std::cout << "requestLobbyJoin : Data corrupted (index)" << std::endl;
        return false;
    }

    playerIndex_ = playerindex;

    return true;
}

bool Client::requestLobbyDisconnect() {

    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 12, rep;

    p << state << sf::String(lobbyIndex_);
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "requestLobbyDisconnect : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "requestLobbyDisconnect : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 12) {
        std::cout << "requestLobbyDisconnect : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "requestLobbyDisconnect : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "requestLobbyDisconnect : Lobby not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "requestLobbyDisconnect : Lobby is not ready." << std::endl;
        return false;
    }

    if (rep == 3) {
        std::cout << "requestLobbyDisconnect : Player not found." << std::endl;
        return false;
    }

    sf::Uint8 resstate;
    p >> resstate;

    if (!p) {
        std::cout << "requestLobbyDisconnect : Data corrupted (resstate)" << std::endl;
        return false;
    }

    if(resstate != 50)
        requestLobbyList();

    return true;
}

bool Client::requestLaunchGame() {

    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 20, rep;

    p << state << sf::String(lobbyIndex_);
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "requestLaunchGame : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "requestLaunchGame : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 20) {
        std::cout << "requestLaunchGame : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "requestLaunchGame : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "requestLaunchGame : Lobby not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "requestLaunchGame : Lobby not filled." << std::endl;
        return false;
    }

    if (rep == 3) {
        std::cout << "requestLaunchGame : Players not ready." << std::endl;
        return false;
    }

    return true;
}

bool Client::sendEndGame() {

    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 21, rep;

    p << state << sf::String(lobbyIndex_);
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "sendEndGame : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "sendEndGame : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 21) {
        std::cout << "sendEndGame : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "sendEndGame : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "sendEndGame : Wrong lobby." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "sendEndGame : Lobby is in wrong state." << std::endl;
        return false;
    }

    if (rep == 3) {
        std::cout << "sendEndGame : Player not found." << std::endl;
        return false;
    }

    return true;
}






bool Client::sendPauseGame() {
    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 22, rep;

    p << state << sf::String(lobbyIndex_);
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "sendPauseGame : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "sendPauseGame : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 22) {
        std::cout << "sendPauseGame : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "sendPauseGame : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "sendPauseGame : Lobby not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "sendPauseGame : Lobby not playing." << std::endl;
        return false;
    }

    return true;
}

bool Client::sendResumeGame() {
    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 23, rep;

    p << state << sf::String(lobbyIndex_);
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "sendResumeGame : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "sendResumeGame : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 23) {
        std::cout << "sendResumeGame : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "sendResumeGame : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "sendResumeGame : Lobby not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "sendResumeGame : Lobby not playing." << std::endl;
        return false;
    }

    return true;
}

bool Client::sendReady(sf::Uint32 color)
{
    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 24, rep;

    p << state << sf::String(lobbyIndex_) << color;
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "sendReady : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "sendReady : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 24) {
        std::cout << "sendReady : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "sendReady : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "sendReady : Lobby not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "sendReady : Lobby not filling." << std::endl;
        return false;
    }

    if (rep == 3) {
        std::cout << "sendReady : Player not found." << std::endl;
        return false;
    }

    return true;
}

bool Client::requestBeatmapChange(const std::string& beatmap, const std::string& mode)
{
    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 25, rep;

    p << state << sf::String(lobbyIndex_) << sf::String(beatmap) << sf::String(mode);
    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "sendResumeGame : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "sendResumeGame : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 23) {
        std::cout << "sendResumeGame : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "sendResumeGame : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "sendResumeGame : Lobby not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "sendResumeGame : Lobby not ready." << std::endl;
        return false;
    }

    return true;
}

bool Client::requestPing()
{
    auto current_time = std::chrono::steady_clock::now();
    sf::Packet packet;

    sf::Int64 send = std::chrono::steady_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    sf::Uint8 state = 1;

    packet << challengeResponse_ << state << send;

    udpSocket_.send(packet, SERVER_IP, SERVER_GAME_PORT);

    return false;
}
