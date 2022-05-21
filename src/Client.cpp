//
// Created by cyril on 16/05/2022.
//

#include "Client.h"
#include "Random.h"

Client::Client() : clientSocket_("client") {
    clientSeed_ = Random::rand();
    challengeResponse_ = 0;
    //clientSocket_.setVerbose(true);
    clientSocket_.setBlocking(false);
    clientSocket_.bind(sf::Socket::AnyPort);
}

bool Client::connectToServer() {
    sf::Packet packet;
    sf::Uint8 state = 0;
    clientSocket_.setBlocking(true);
    packet << state << clientSeed_;
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
