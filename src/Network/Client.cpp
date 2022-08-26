//
// Created by cyril on 16/05/2022.
//

#include "Client.h"
#include "../System/Random.h"
#include "Lobby.h"

Client::Client(std::string name) : clientSocket_(name), lobbyList_(SERVER_NB_MAX_LOBBY) {
    name_ = name;
    clientSeed_ = Random::rand();
    challengeResponse_ = 0;
    clientSocket_.setVerbose(false);
    clientSocket_.setBlocking(false);
    clientSocket_.bind(sf::Socket::AnyPort);
    playerIndex_ = 0;

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

bool Client::connectToServer() {
    sf::Packet packet;
    sf::Uint8 state = 0;
    clientSocket_.setBlocking(true);
    packet << state << clientSeed_ << name_;
    clientSocket_.send(packet, SERVER_IP, SERVER_CONNECT_PORT);
    if(clientSocket_.recieve()) {
        sf::Int32 serverSeed;
        clientSocket_.getRecievedPacket() >> state >> serverSeed;
        if(state == 1) {
            challengeResponse_ = clientSeed_ ^ serverSeed;

            packet.clear();
            packet << state << challengeResponse_;
            clientSocket_.send(packet, SERVER_IP, SERVER_CONNECT_PORT);
            if(clientSocket_.recieve()) {
                clientSocket_.getRecievedPacket() >> state;
                if(state == 2) {
                    clientSocket_.getRecievedPacket() >> index_;
                    std::cout << index_ << " ";
                    clientSocket_.setBlocking(false);
                    packetID_ = 0;
                    return true;
                }
            }
        }
    }

    clientSocket_.setBlocking(false);
    return false;
}

bool Client::disconectToServer() {

    sf::Packet packet;
    sf::Uint8 state = 50;
    packet << state << challengeResponse_;

    clientSocket_.setBlocking(true);

    clientSocket_.send(packet, SERVER_IP, SERVER_CONNECT_PORT);
    if(clientSocket_.recieve()) {
        clientSocket_.setBlocking(false);
        return true;
    }
    clientSocket_.setBlocking(false);
    return false;
}

void Client::sendCommand(const std::string& cmd) {
    clientSocket_.setBlocking(true);
    sf::Packet packet;
    packet << cmd;
    clientSocket_.send(packet, SERVER_IP, SERVER_ADMIN_PORT);
    if(clientSocket_.recieve()) {
        std::string msg;
        clientSocket_.getRecievedPacket() >> msg;
        std::cout << msg << std::endl;
    }
    clientSocket_.setBlocking(false);
}

void Client::sendPlayerData(sf::Int32 x, sf::Int32 y) {
    sf::Packet packet;
    packet << challengeResponse_ << packetID_ << x << y;
    clientSocket_.send(packet, SERVER_IP, SERVER_GAME_PORT);
    packetID_++;
}

int Client::updateFromServerPlayerPosition(std::vector<Joueur> &joueurs, std::pair<float, float> &checkpoint) {
    if(clientSocket_.recieve()) {
        sf::Uint8 state = 0, dummy;

        clientSocket_.getRecievedPacket() >> state;

        if(state == 0) {
            for(int i = 0; i < joueurs.size(); i++) {
                joueurs[i].setDataFromServer(clientSocket_.getRecievedPacket());
            }
        }
        else if(state == 33) { // INTERRUPT
            clientSocket_.getRecievedPacket() >> dummy;
            return 1;
        }
        else if (state == 34) { // PAUSE
            clientSocket_.getRecievedPacket() >> checkpoint.first >> checkpoint.second;
            return 2;
        }
        else if (state == 35) { // RESUME
            clientSocket_.getRecievedPacket() >> dummy;
            return 3;
        }


    }

    return 0;
}

void Client::changeName(const std::string& name)
{
    name_ = name;
}

bool Client::sendEndGame() {
    clientSocket_.setBlocking(true);
    sf::Packet p;
    sf::Uint8 state = 21, dummy;

    p << state << challengeResponse_ << lobbyIndex_;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if (clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state >> dummy;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestLobbyCreation(const std::string& name, const std::string &beatmap, const std::string &mode) {
    clientSocket_.setBlocking(true);

    sf::Packet p;
    sf::Uint8 state = 10;

    p << state << challengeResponse_ << name << beatmap << mode;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if(clientSocket_.recieve()) {
        std::string index;
        clientSocket_.getRecievedPacket() >> state;
        if(state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
        clientSocket_.getRecievedPacket() >> index;
        lobbyIndex_ = index;
        playerIndex_ = 0;
        std::cout << "Index : " << lobbyIndex_ << std::endl;

        requestLobbyList();
        lobbyInd_ = findLobbyById(lobbyList_, index);
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestLobbyList() {
    clientSocket_.setBlocking(true);

    sf::Packet p;
    sf::Uint8 state = 40;

    p << state << challengeResponse_;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if(clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state;
        if(state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }

        for(int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
            sf::Uint8 status;
            clientSocket_.getRecievedPacket() >> status >> lobbyList_[i].id
                                              >> lobbyList_[i].name
                                              >> lobbyList_[i].nbIn >> lobbyList_[i].limit
                                              >> lobbyList_[i].players[0]->name;

            lobbyList_[i].status = static_cast<LobbyStatus>(status);
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestLobbyInfo(const std::string& lobbyIndex) {
    clientSocket_.setBlocking(true);

    sf::Packet p;
    sf::Uint8 state = 41;

    p << state << challengeResponse_ << lobbyIndex;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if(clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state;

        if(state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
        int id = findLobbyById(lobbyList_, lobbyIndex);
        clientSocket_.getRecievedPacket() >> lobbyList_[id].name;
        clientSocket_.getRecievedPacket() >> lobbyList_[id].nbIn;
        clientSocket_.getRecievedPacket() >> lobbyList_[id].limit;
        clientSocket_.getRecievedPacket() >> lobbyList_[id].beatmap;
        clientSocket_.getRecievedPacket() >> lobbyList_[id].mode;

        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
            sf::Uint8 status;
            clientSocket_.getRecievedPacket() >> status >> lobbyList_[id].players[i]->name >> lobbyList_[id].players[i]->color;
            lobbyList_[id].players[i]->status = (PlayerStatus)status;
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestLobbyJoin(const std::string &lobbyIndex) {
    clientSocket_.setBlocking(true);
    sf::Packet p;
    sf::Uint8 state = 11;
    lobbyIndex_ = lobbyIndex;
    p << state << challengeResponse_ << lobbyIndex_;
    lobbyInd_ = findLobbyById(lobbyList_, lobbyIndex_);

    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if(clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state >> playerIndex_;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }
    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestLobbyDisconnect() {
    sf::Packet p;
    sf::Uint8 state = 12, dummy;

    clientSocket_.setBlocking(true);

    p << state << challengeResponse_ << lobbyIndex_;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if(clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state >> dummy;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }

    clientSocket_.setBlocking(false);
    requestLobbyList();
    return true;
}

bool Client::monitorLobby(int &roomState) {
    bool ok = true;
    if(clientSocket_.recieve()) {
        sf::Uint8 state;
        clientSocket_.getRecievedPacket() >> state;
        if(state == 30) { //Start Game
            sf::Uint8 ind;
            clientSocket_.getRecievedPacket() >> ind;
            index_ = ind;
            roomState = 1;
        }
        else if(state == 31) { // Lobby Disband
            sf::Uint8 dummy;
            clientSocket_.getRecievedPacket() >> dummy;
            roomState = -1;
        }
        else if(state == 32) { // Refresh Lobby Info
            sf::Uint8 dummy;
            clientSocket_.getRecievedPacket() >> dummy;
            roomState = 2;
            //ok = requestLobbyInfo(lobbyIndex_);
        }
    }
    return ok;
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

bool Client::requestLaunchGame() {
    clientSocket_.setBlocking(true);
    sf::Packet p;
    sf::Uint8 state = 20, dummy;

    p << state << challengeResponse_ << lobbyIndex_;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if (clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state >> dummy;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::sendPauseGame() {
    clientSocket_.setBlocking(true);
    sf::Packet p;
    sf::Uint8 state = 22, dummy;

    p << state << challengeResponse_ << lobbyIndex_;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if (clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state >> dummy;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::sendResumeGame() {
    clientSocket_.setBlocking(true);
    sf::Packet p;
    sf::Uint8 state = 23, dummy;

    p << state << challengeResponse_ << lobbyIndex_;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if (clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state >> dummy;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::sendReady(sf::Uint32 color)
{
    clientSocket_.setBlocking(true);
    sf::Packet p;
    sf::Uint8 state = 24, dummy;

    p << state << challengeResponse_ << lobbyIndex_ << color;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if (clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state >> dummy;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestBeatmapChange(const std::string& beatmap, const std::string& mode)
{
    clientSocket_.setBlocking(true);
    sf::Packet p;
    sf::Uint8 state = 25, dummy;

    p << state << challengeResponse_ << lobbyIndex_ << beatmap << mode;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if (clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state >> dummy;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}
