//
// Created by cyril on 13/05/2022.
//

#include "Server.h"

#include <SFML/Network.hpp>

#include <iostream>
#include "Random.h"

Server::Server() :  admin("admin", SERVER_ADMIN_PORT, false),
                    connect("connect", SERVER_CONNECT_PORT, false),
                    game("game", SERVER_GAME_PORT, false){
    serverSeed = Random::rand();

    for(int i = 0; i < NB_MAX_JOUEURS; i++) {
        connectedPlayers.emplace_back();
    }
}


void Server::run() {
    bool loop = true;
    serverTick.restart();
    while(loop) {
        monitorAdminCommand(loop);
        monitorConnectRequest();
        monitorPlayerData();
        sendPlayerData();
    }
}

void Server::monitorAdminCommand(bool &loop) {
    if(admin.recieve()) {
        std::string cmd;
        admin.getRecievedPacket() >> cmd;
        std::cout << "ADMIN : " << cmd << std::endl;
        sf::Packet packet;
        if(cmd == "quit") {
            loop = false;
            packet << "Server exited";
            admin.send(packet, admin.getSender(), admin.getSenderPort());
        }

        else if(cmd == "name") {
            packet << SERVER_NAME;
            admin.send(packet, admin.getSender(), admin.getSenderPort());
        }
        else if(cmd == "version") {
            packet << SERVER_VERSION;
            admin.send(packet, admin.getSender(), admin.getSenderPort());
        }
        else if(cmd == "NB_CONNECTED") {
            packet << std::to_string(connectedPlayers.size());
            admin.send(packet, admin.getSender(), admin.getSenderPort());
        }
        else if(cmd == "timeout") {

        }
        else{
            packet << "Command not found";
            admin.send(packet, admin.getSender(), admin.getSenderPort());
        }
    }
}

void Server::monitorConnectRequest() {
    if(connect.recieve()) {
        sf::Uint8 state;
        sf::Packet packet;

        connect.getRecievedPacket() >> state;
        if(state == 50) {
            int index = findConnected(connect.getSender(), connect.getSenderPort());
            if(index != -1) {
                sf::Int32 challengeResponse,
                        solution = connectedPlayers[index].seed ^ serverSeed;

                connect.getRecievedPacket() >> challengeResponse;

                if(challengeResponse == solution) {
                    std::cout << "CONNECT : disconnection " <<
                              connect.getSender() << " (" << connect.getSenderPort() << ")" << std::endl;

                    packet << state;
                    connect.send(packet, connect.getSender(), connect.getSenderPort());
                    connectionState[connect.getID()].clear();
                    connectedPlayers[index].connected = false;
                }
                else
                    state = 100;
            }
            else
                state = 100;
        }


        if(checkConnected(connect.getSender(), connect.getSenderPort()))
            state = 100;
        if(connectedPlayers.size() > SERVER_NB_MAX_PLAYERS)
            state = 100;

        if(state == 0) {
            sf::Int32 seed;
            connect.getRecievedPacket() >> seed;

            connectionState[connect.getID()] = PlayerInfo(connect.getSender(),
                                                              connect.getSenderPort(), seed);
            state++;
            connectionState[connect.getID()].state = state;
            packet << state << serverSeed;
            connect.send(packet, connect.getSender(), connect.getSenderPort());

        }
        else if(state == 1 && connectionState[connect.getID()].state == 1) {
            sf::Int32 challengeResponse,
            solution = connectionState[connect.getID()].seed ^ serverSeed;
            connect.getRecievedPacket() >> challengeResponse;


            if(challengeResponse == solution) {
                state++;
                connectionState[connect.getID()].state = state;
                sf::Int32 index = findFistAvailableConnected();
                packet << state << index;
                connect.send(packet, connect.getSender(), connect.getSenderPort());

                connectedPlayers[index] = connectionState[connect.getID()];
                connectedPlayers[index].connected = true;
                connectedPlayers[index].packetID = 0;

                std::cout << "CONNECT : new connection " <<
                    connect.getSender() << " (" << connect.getSenderPort() << ")" << std::endl;

                connectionState[connect.getID()].clear();
            }
            else {
                state = 100;
            }
        }
        else
            state = 100;

        if(state == 100) {
            packet.clear();
            packet << state;
            connect.send(packet, connect.getSender(), connect.getSenderPort());
            connectionState[connect.getID()].clear();
        }
    }
}

bool Server::checkConnected(sf::IpAddress address, unsigned short port) {

    for(size_t i = 0; i < connectedPlayers.size(); i++) {
        if(connectedPlayers[i].connected &&
            address == connectedPlayers[i].address &&
            port == connectedPlayers[i].port)
            return true;
    }

    return false;
}

int Server::findConnected(sf::IpAddress address, unsigned short port) {
    for(size_t i = 0; i < connectedPlayers.size(); i++) {
        if(connectedPlayers[i].connected &&
            address == connectedPlayers[i].address &&
            port == connectedPlayers[i].port)
            return i;
    }
    return -1;
}

void Server::monitorPlayerData() {
    if(game.recieve()) {
        int ind = findConnected(game.getSender(), game.getSenderPort());
        if(ind != -1) {
            sf::Uint16 pid = 0;
            game.getRecievedPacket() >> pid;

            if(Utils::sequence_greater_than(pid, connectedPlayers[ind].packetID)) {
                connectedPlayers[ind].packetID = pid;
                game.getRecievedPacket() >> connectedPlayers[ind].x >> connectedPlayers[ind].y;
            }
        }
    }
}

void Server::sendPlayerData() {
    if(serverTick.getElapsedTime().asMilliseconds() > SERVER_TICK_MS) {
        sf::Packet packet;

        for(int i = 0; i < connectedPlayers.size(); i++) {
            packet << connectedPlayers[i].connected << connectedPlayers[i].x << connectedPlayers[i].y;
        }
        for(int i=0; i < connectedPlayers.size(); i++) {
            if(connectedPlayers[i].connected) {
                game.send(packet, connectedPlayers[i].address, connectedPlayers[i].port);
            }
        }

        serverTick.restart();
    }

}

int Server::findFistAvailableConnected() {
    for(int i = 0; i< connectedPlayers.size(); i++) {
        if(!connectedPlayers[i].connected)
            return i;
    }
    return -1;
}
