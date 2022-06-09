//
// Created by cyril on 16/05/2022.
//

#include "Client.h"
#include "Random.h"
#include "Lobby.h"

Client::Client(std::string name) : clientSocket_(name) {
    name_ = name;
    clientSeed_ = Random::rand();
    challengeResponse_ = 0;
    clientSocket_.setVerbose(true);
    clientSocket_.setBlocking(false);
    clientSocket_.bind(sf::Socket::AnyPort);
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
    packet << packetID_ << x << y;
    clientSocket_.send(packet, SERVER_IP, SERVER_GAME_PORT);
    packetID_++;
}

void Client::updateFromServerPlayerPosition(std::vector<Joueur> &joueurs) {
    if(clientSocket_.recieve()) {
        for(int i = 0; i < joueurs.size(); i++) {
            joueurs[i].setDataFromServer(clientSocket_.getRecievedPacket());
        }
    }
}

bool Client::requestLobbyCreation(std::string &lobbyIndex, std::string name) {
    clientSocket_.setBlocking(true);

    sf::Packet p;
    sf::Uint8 state = 10;

    p << state << challengeResponse_ << name;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if(clientSocket_.recieve()) {
        std::string index;
        clientSocket_.getRecievedPacket() >> state;
        if(state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
        clientSocket_.getRecievedPacket() >> index;
        lobbyIndex = index;

    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestLobbyList(std::vector<Lobby> &lobbylist) {
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
            clientSocket_.getRecievedPacket() >> status >>lobbylist[i].id
                                              >> lobbylist[i].name
                                              >> lobbylist[i].nbIn >> lobbylist[i].limit
                                              >> lobbylist[i].players[0]->name;

            lobbylist[i].status = static_cast<LobbyStatus>(status);
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestLobbyInfo(Lobby &lobby, const std::string& id) {
    clientSocket_.setBlocking(true);

    sf::Packet p;
    sf::Uint8 state = 41;

    p << state << challengeResponse_ << id;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if(clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state;

        if(state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }

        clientSocket_.getRecievedPacket() >> lobby.name;
        clientSocket_.getRecievedPacket() >> lobby.nbIn;
        clientSocket_.getRecievedPacket() >> lobby.limit;

        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
            clientSocket_.getRecievedPacket() >> lobby.players[i]->name;
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestLobbyJoin(std::vector<Lobby> &lobbylist, std::string& lobbyIndex) {
    clientSocket_.setBlocking(true);
    sf::Packet p;
    sf::Uint8 state = 11;

    p << state << challengeResponse_ << lobbyIndex;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if(clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }

    clientSocket_.setBlocking(false);
    return true;
}

bool Client::requestLobbyDisconnect(std::vector<Lobby> &lobbylist, std::string& lobbyIndex) {
    sf::Packet p;
    sf::Uint8 state = 12;

    clientSocket_.setBlocking(true);

    p << state << challengeResponse_ << lobbyIndex;
    clientSocket_.send(p, SERVER_IP, SERVER_LOBBY_PORT);

    if(clientSocket_.recieve()) {
        clientSocket_.getRecievedPacket() >> state;
        if (state == 100) {
            clientSocket_.setBlocking(false);
            return false;
        }
    }


    clientSocket_.setBlocking(false);
    return true;
}

bool Client::monitorLobby(std::vector<Lobby> &lobbylist, std::string &roomID) {
    bool ok = true;
    if(clientSocket_.recieve()) {
        sf::Uint8 state;
        clientSocket_.getRecievedPacket() >> state;
        if(state == 30) { //Start Game

        }
        else if(state == 31) { // Lobby Disband
            sf::Uint8 dummy;
            clientSocket_.getRecievedPacket() >> dummy;
            ok = requestLobbyDisconnect(lobbylist, roomID);
        }
        else if(state == 32) { // Refresh Lobby Info
            sf::Uint8 dummy;
            clientSocket_.setBlocking(true);
            clientSocket_.getRecievedPacket() >> dummy;
            int index = findLobbyById(lobbylist, roomID);
            ok = requestLobbyInfo(lobbylist[index], roomID);
        }
    }
    return ok;
}
