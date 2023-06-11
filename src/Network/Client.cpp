//
// Created by cyril on 16/05/2022.
//

#include "Client.h"
#include "../System/Random.h"
#include "Lobby.h"
#include <chrono>
#include <thread>

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

float Client::getPosition()
{
    return position_;
}

unsigned short Client::getUdpPort()
{
    return udpSocket_.getPort();
}

bool Client::getGodMode()
{
    return godMode_;
}

bool Client::keepAlive()
{
    if (keepAliveTimer_.getElapsedTime() > sf::seconds(KEEP_ALIVE_TIMER)) {
        keepAliveTimer_.restart();
        sf::Packet p_tcp, p_udp;
        sf::Uint8 stateTCP = 19, stateUDP = 19;

        sf::Socket::Status status;

        p_tcp << stateTCP;
        p_udp << playerID_ << challengeResponse_ << stateUDP;

        status =  tcpSocket_.send(p_tcp);
        if (status != sf::Socket::Done) {
            std::cout << "keepAlive : Unable to reach the server (tcp)" << std::endl;
            return false;
        }

        bool val = udpSocket_.send(p_udp, SERVER_IP, SERVER_GAME_PORT);
        if (!val) {
            std::cout << "keepAlive : Unable to reach the server (udp)" << std::endl;
            return false;
        }
    }

    return true;
}

void Client::changeName(const std::string& name)
{
    name_ = name;
}

void Client::setProfile(const Profile& profile)
{
    name_ = profile.getName();
    bannerId_ = profile.getBannerId();
    titleId_ = profile.getTitleId();
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
    sf::Int32 serverSeed, bannerID, titleID;

    bannerID = bannerId_;
    titleID = titleId_;


    p << state << sf::String(name_) << bannerID << titleID << clientSeed_;
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
    sf::Uint32 playerID;
    p >> rep >> playerID;

    if (!p) {
        std::cout << "connectToServer : Data corrupted (playerID)" << std::endl;
        return false;
    }

    playerID_ = playerID;
    

    p.clear();
    //std::cout << clientSeed_ << std::endl;
    p << clientSeed_;
    udpSocket_.send(p, SERVER_IP, SERVER_LOGIN_PORT);

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
    packet << playerID_ << challengeResponse_ << state << packetID_ << x << y;
    udpSocket_.send(packet, SERVER_IP, SERVER_GAME_PORT);
    packetID_++;
}

int Client::updateFromServerPlayerPosition(std::vector<Joueur> &joueurs, std::pair<float, float> &checkpoint, EntityManager& em) {


    sf::Packet packet;
    sf::Socket::Status status = receiveWithTimeout(tcpSocket_, packet, sf::milliseconds(SERVER_SLEEP));

    if (status == sf::Socket::Done) {
        

        sf::Uint8 state;
        packet >> state;

        std::cout << "updateFromServerPlayerPosition : Packet recieved (" << (int)state << ")" << std::endl;

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

            sf::Uint64 startTime;
            sf::Uint8 dummy;
            packet >> dummy >> startTime;

            if (!packet) {
                std::cout << "updateFromServerPlayerPosition : Can't read time." << std::endl;
                return 0;
            }

            startTime_ = startTime;

            return 3;
        }
        if (state == 36) {
            fetchRandomSequence(packet, em);
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
            sf::Uint64 serverTime, clientTime, clientSentTime;
            sf::Int32 godmode;
            float position;
            udpSocket_.getRecievedPacket() >> clientSentTime >> serverTime >> beat >> position >> godmode;

            if (!udpSocket_.valid()) {
                std::cout << "GAME PORT : Data corrupted (updateFromServerPlayerPosition - 1)." << std::endl;
                return 0;
            }

            serverBeat_ = beat;

            clientTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
            position_ = position +(clientTime - clientSentTime) / 2000.f;
            ping_[pingIndex_] = clientTime - clientSentTime;
            pingIndex_++;
            pingIndex_ = pingIndex_ % ping_.size();
            godMode_ = godmode == 1;

            return 4;
        }
    }
        
    

    return 0;
}




bool Client::monitorLobby(int& roomState, EntityManager& em) {

    
    sf::Packet packet;
    sf::Socket::Status status = receiveWithTimeout(tcpSocket_, packet, sf::milliseconds(SERVER_SLEEP));

    if (status == sf::Socket::Done) {

        sf::Uint8 state;
        packet >> state;

        if (!packet) {
            std::cout << "monitorLobby : Can't read state." << std::endl;
            return false;
        }

        std::cout << "monitorLobby : Packet recieved (" << (int)state << ")" << std::endl;

        if (state == 30) { //Start Game
            sf::Uint8 ind;
            sf::Uint64 startTime;
            packet >> ind >> startTime;

            if (!packet) {
                std::cout << "monitorLobby : Data Corupted (30)." << std::endl;
                return false;
            }


            index_ = ind;
            startTime_ = startTime;
            

            roomState = 1;
        }
        if (state == 31) { // Lobby Disband
            roomState = -1;
        }
        if (state == 32) { // Refresh Lobby Info
            roomState = 2;
        }
        if (state == 36) { // Random Sequence
            fetchRandomSequence(packet, em);
        }
    }

    return true;
}

void Client::fetchRandomSequence(sf::Packet& p, EntityManager& em)
{
    em.deleteSequences();
    sf::Int32 nb;
    p >> nb;
    if (!p) {
        std::cout << "fetchRandomSequence : Data corrupted (nb)" << std::endl;
        return;
    }
    for (int i = 0; i < nb; i++) {
        sf::Int32 nb2;
        p >> nb2;
        if (!p) {
            std::cout << "fetchRandomSequence : Data corrupted (nb2 " << i << ")" << std::endl;
            return;
        }
        std::cout << "Fetch sequence : ";
        em.initRandomSequence(nb2);
        for (int j = 0; j < nb2; j++) {
            sf::Int32 val;
            p >> val;
            if (!p) {
                std::cout << "fetchRandomSequence : Data corrupted (val " << i << " " << j   <<")" << std::endl;
                return;
            }
            em.setRandomSequenceVal(i, j, val);
        }
        std::cout << std::endl;
        
    }

}

bool Client::waitToStart()
{
    sf::Packet p;
    sf::Uint8 state, rep;
    sf::Socket::Status status;

    std::vector<sf::Int64> offset;
    for (int i = 0; i < 5; i++) {
        p.clear();
        state = 120;

        sf::Uint64 send = std::chrono::steady_clock::now().time_since_epoch() / std::chrono::milliseconds(1);

        p << state << send;
        status = tcpSocket_.send(p);
        if (status != sf::Socket::Done) {

            std::cout << "waitToStart : Unable to reach the server (send)" << std::endl;
            return false;
        }

        p.clear();
        status = receiveWithTimeout(tcpSocket_, p);

        p >> state;
        if (!p) {
            std::cout << "waitToStart : Data corrupted (state2)" << std::endl;
            return false;
        }

        if (state != 120) {
            std::cout << "waitToStart : Unexpected packet recieved (" << (int)state << ")" << std::endl;
            return false;
        }

        p >> rep;

        if (!p) {
            std::cout << "waitToStart : Data corrupted (rep2)" << std::endl;
            return false;
        }

        if (rep == 1) {
            std::cout << "waitToStart : Data corrupted." << std::endl;
            return false;
        }

        sf::Uint64 clientSentTime, serverTime;

        p >> clientSentTime >> serverTime;

        if (!p) {
            std::cout << "waitToStart : Data corrupted (time)" << std::endl;
            return false;
        }

        sf::Uint64 currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

        sf::Int64 travel = (currentTime - clientSentTime) / 2;

        offset.push_back(serverTime - currentTime + travel);

        std::cout << "   Offset : " << offset.back() << std::endl;

    }

    std::sort(offset.begin(), offset.end());
    offset_ = offset[2];


    std::cout << "Server Start : " << startTime_ << std::endl;


    sf::Uint64 currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();;

    std::cout << "CurentTime : " << currentTime << std::endl;
    std::cout << "CurentTime + offset : " << currentTime + offset_ << std::endl;

    while (currentTime + offset_ < startTime_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(SERVER_SLEEP));
        currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        //std::cout << currentTime << " " << currentTime + offset_ << " " << startTime_ << std::endl;
    }


    std::cout << "GAME STARTED " << std::endl;
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
    sf::String lobyname, playername, beatmap;
    sf::Int32 banner, title;

    p >> lobyname >> nbIn >> limit >> beatmap;

    if (!p) {
        std::cout << "requestLobbyInfo : Data corrupted (header)" << std::endl;
        return false;
    }

    lobbyList_[id].name = lobyname;
    lobbyList_[id].nbIn = nbIn;
    lobbyList_[id].limit = limit;
    lobbyList_[id].beatmap = beatmap;

    for (int i = 0; i < NB_MAX_JOUEURS; i++) {
        p >> playerstatus >> playername >> color >> banner >> title;

        if (!p) {
            std::cout << "requestLobbyInfo : Data corrupted (" << i << ")" << std::endl;
            return false;
        }
        lobbyList_[id].players[i]->name = playername;
        lobbyList_[id].players[i]->color = color;
        lobbyList_[id].players[i]->status = (PlayerStatus)playerstatus;
        lobbyList_[id].players[i]->bannerID = banner;
        lobbyList_[id].players[i]->titleID = title;
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
        std::cout << "requestBeatmapChange : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "requestBeatmapChange : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 23) {
        std::cout << "requestBeatmapChange : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "requestBeatmapChange : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "requestBeatmapChange : Lobby not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "requestBeatmapChange : Lobby not ready." << std::endl;
        return false;
    }

    return true;
}

bool Client::requestPing()
{
    sf::Packet packet;

    sf::Uint64 send = std::chrono::steady_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
    sf::Uint8 state = 1;

    packet << playerID_ << challengeResponse_ << state << send;

    udpSocket_.send(packet, SERVER_IP, SERVER_GAME_PORT);

    return false;
}

bool Client::requestRoomStatus(RoomStatus *roomStatus, EntityManager& em, const std::string& lobbyIndex)
{
    sf::Socket::Status status;

    sf::Packet p;
    sf::Uint8 state = 26, rep;

    if(lobbyIndex == "") 
        p << state << sf::String(lobbyIndex_);
    else
        p << state << sf::String(lobbyIndex);

    status = tcpSocket_.send(p);
    if (status != sf::Socket::Done) {
        std::cout << "requestRoomStatus : Unable to reach the server (send)" << std::endl;
        return false;
    }

    p.clear();
    status = receiveWithTimeout(tcpSocket_, p);

    p >> state;
    if (!p) {
        std::cout << "requestRoomStatus : Data corrupted (state)" << std::endl;
        return false;
    }

    if (state != 26) {
        std::cout << "requestRoomStatus : Unexpected packet recieved (" << (int)state << ")" << std::endl;
        return false;
    }

    p >> rep;

    if (!p) {
        std::cout << "requestRoomStatus : Data corrupted (rep)" << std::endl;
        return false;
    }

    if (rep == 1) {
        std::cout << "requestRoomStatus : Lobby not found." << std::endl;
        return false;
    }

    if (rep == 2) {
        std::cout << "requestRoomStatus : Lobby not ready." << std::endl;
        return false;
    }

    sf::Int32 size;
    float beat;
    p >> beat >> size;

    if (!p) {
        std::cout << "requestRoomStatus : Data corrupted (size1)" << std::endl;
        return false;
    }

    roomStatus->setBeat(beat);

    std::cout << "Current beat : " << beat << std::endl;
    std::cout << "Failed mechs : " << size << std::endl;

    for (int i = 0; i < size; i++) {
        sf::Int32 failed;
        p >> failed;

        if (!p) {
            std::cout << "requestRoomStatus : Data corrupted (failed << " << i << ")" << std::endl;
            return false;
        }

        roomStatus->addFailed(failed);

        std::cout << "      " << failed << " " << std::endl;
    }

    p >> size;

    if (!p) {
        std::cout << "requestRoomStatus : Data corrupted (size2)" << std::endl;
        return false;
    }

    std::cout << "Drawn mechs : " << size << std::endl;

    for (int i = 0; i < size; i++) {
        sf::Int32 nbTargets, mech;
        p >> mech >> nbTargets;

        if (!p) {
            std::cout << "requestRoomStatus : Data corrupted (nbTargets " << i << ")" << std::endl;
            return false;
        }
        std::vector<sf::Vector2f> targets;
        for (int j = 0; j < nbTargets; j++) {
            float x, y;
            p >> x >> y;


            if (!p) {
                std::cout << "requestRoomStatus : Data corrupted (draw pos " << i << "-" << j << "/ " << nbTargets << ")" << std::endl;
                return false;
            }

            targets.emplace_back(x, y);

            std::cout << "      " << mech << " - (" << x << ";" << y << ")" << std::endl;
        }

        roomStatus->setMechPosition(mech, targets);
    }



    float zoom, rotation, top, left, width, height;

    p >> size >> zoom >> rotation >> top >> left >> width >> height;

    std::cout << "Zoom : " << zoom << std::endl;
    std::cout << "Rotation : " << rotation << std::endl;
    std::cout << "Top : " << top << std::endl;
    std::cout << "Left : " << left << std::endl;
    std::cout << "width : " << width << std::endl;
    std::cout << "Height : " << height << std::endl;



    if (!p) {
        std::cout << "requestRoomStatus : Data corrupted (arena)" << std::endl;
        return false;
    }

    roomStatus->setArenaParameters(zoom, rotation, left, top, width, height);

    std::cout << "Arena : " << size << std::endl;

    for (int i = 0; i < size; i++) {
        float rt, rl, rw, rh;
        p >> rt >> rl >> rw >> rh;

        if (!p) {
            std::cout << "requestRoomStatus : Data corrupted (arena < " << i << ")" << std::endl;
            return false;
        }

        roomStatus->addArenaRect(rl, rt, rw, rh);

        std::cout << "      " << rt << " " << rl << " " <<
            rw << " " << rh << " " << std::endl;
    }

    std::cout << "Totems : " << std::endl;
    for (int i = 0; i < NB_MAX_TOTEM; i++) {
        sf::Uint32 color;
        sf::Int32 active;
        sf::Int32 x, y;

        p >> color >> active >> x >> y;

        if (!p) {
            std::cout << "requestRoomStatus : Data corrupted (totems < " << i << ")" << std::endl;
            return false;
        }
        roomStatus->addTotem(i, color, active == 1, x, y);

        std::cout << "      " << color << " " << active << " " <<
            x << " " << y << " " << std::endl;
    }

    std::cout << "Joueurs : " << std::endl;
    for (int i = 0; i < NB_MAX_JOUEURS; i++) {
        sf::String name;
        sf::Uint32 color;
        sf::Int32 active;
        sf::Int32 x, y;

        p >> name >> color >> active >> x >> y;

        std::string stdName = name;

        if (!p) {
            std::cout << "requestRoomStatus : Data corrupted (players < " << i << ")" << std::endl;
            return false;
        }

        roomStatus->addJoueur(i, stdName, color, active == 1, x, y);

        std::cout << "      " << stdName << " " << color << " " << active << " " <<
            x << " " << y << " " << std::endl;
    }


    std::cout << "Debuffs : " << std::endl;

    for (int i = 0; i < NB_MAX_JOUEURS; i++) {
        sf::Int32 nbTargets;
        p >> nbTargets;

        if (!p) {
            std::cout << "requestRoomStatus : Data corrupted (Debuffs " << i << ")" << std::endl;
            return false;
        }
        for (int j = 0; j < nbTargets; j++) {
            sf::Int32 type;
            float endTime;
            p >> type >> endTime;


            if (!p) {
                std::cout << "requestRoomStatus : Data corrupted (debuff infos " << i << "-" << j << "/ " << nbTargets << ")" << std::endl;
                return false;
            }
            roomStatus->setDebuffs(i, DebuffType(type), endTime);
            std::cout << "      " << i << " - " << type << " : " << endTime << std::endl;
        }
    }

    fetchRandomSequence(p, em);



    return false;
}
