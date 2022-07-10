//
// Created by cyril on 13/05/2022.
//

#include "Server.h"

#include <SFML/Network.hpp>
#include <chrono>
#include <thread>
#include <iostream>

#include "../System/Random.h"

Server::Server() :  admin("admin", SERVER_ADMIN_PORT, false),
                    connect("connect", SERVER_CONNECT_PORT, false),
                    game("game", SERVER_GAME_PORT, false),
                    lobby("loby", SERVER_LOBBY_PORT, false){
    serverSeed = Random::rand();

    for(int i = 0; i < SERVER_NB_MAX_PLAYERS; i++) {
        connectedPlayers.emplace_back();
    }

    for(int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
        lobbies.emplace_back();
    }
}


void Server::run() {
    bool loop = true;
    serverTick.restart();

    sf::Clock fps;

    while(loop) {
        sf::Time elapsedTime = fps.getElapsedTime();
        fps.restart();

        monitorAdminCommand(loop);
        monitorConnectRequest();
        monitorLobby();
        monitorPlayerData();
        sendPlayerData();
        updateLobbies(elapsedTime);

        std::this_thread::sleep_for(std::chrono::milliseconds(SERVER_SLEEP));
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
        else if(cmd == "PLAYER_LIST") {
            std::string res;

            for(int i = 0; i < connectedPlayers.size(); i++) {
                if(connectedPlayers[i].status != PlayerStatus::PLAYER_DISCONNECTED) {
                    res += std::to_string(i) + " - " + connectedPlayers[i].name + " " +
                            connectedPlayers[i].address.toString() + ":" +
                            std::to_string(connectedPlayers[i].port)+ "\n";
                    res += "  Status : ";
                    switch(connectedPlayers[i].status) {
                        case PLAYER_DISCONNECTED:
                            res += "PLAYER_DISCONNECTED";
                            break;
                        case PLAYER_IDLE:
                            res += "PLYER_IDLE";
                            break;
                        case PLAYER_WAITING:
                            res += "PLAYER_WAITING";
                            break;
                        case PLAYER_PLAYING:
                            res += "PLAYER_PLAYING";
                            break;
                        case PLAYER_READY:
                            res += "PLAYER_READY";
                            break;
                    }
                    res += "\n";
                    res += "  - Coords : (" + std::to_string(connectedPlayers[i].x) +", "
                            + std::to_string(connectedPlayers[i].y) + ")\n";
                }

            }

            packet << res;
            admin.send(packet, admin.getSender(), admin.getSenderPort());
        }
        else if(cmd == "LOBBY_LIST") {
            std::string res;

            for(int i = 0; i < lobbies.size(); i++) {
                if(lobbies[i].status != LobbyStatus::LOBBY_AVAILABLE){
                    res += std::to_string(i) + " - "
                            + lobbies[i].name + " (" + lobbies[i].id +")\n";
                    res += " - Filling : " +
                            std::to_string(lobbies[i].nbIn) + "/" + std::to_string(lobbies[i].limit);
                    res += " - Status : ";
                    switch(lobbies[i].status) {
                        case LOBBY_AVAILABLE:
                            res += "LOBBY_AVAILABLE";
                            break;
                        case LOBBY_FILLING:
                            res += "LOBBY_FILLING";
                            break;
                        case LOBBY_PLAYING:
                            res += "LOBBY_PLAYING";
                            break;
                    }
                    res+="\n";
                    res += " - Players : \n";
                    for(int j= 0; j < lobbies[i].players.size(); j++) {
                        if(lobbies[i].players[j] == nullptr)
                            res+="\tVIDE\n";
                        else
                            res+="\t"+lobbies[i].players[j]->name+"\n";
                    }
                }
            }
            packet << res;
            admin.send(packet, admin.getSender(), admin.getSenderPort());
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
                    connectedPlayers[index].status = PlayerStatus::PLAYER_DISCONNECTED;

                    return;
                }
                else
                    state = 100;
            }
            else
                state = 100;
        }


        if(checkConnected(connect.getSender(), connect.getSenderPort()))
            state = 100;

        if(state == 0) {
            sf::Int32 seed;
            std::string name;
            connect.getRecievedPacket() >> seed >> name;

            connectionState[connect.getID()] = PlayerInfo(connect.getSender(),
                                                              connect.getSenderPort(), seed, name);
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
                connectedPlayers[index].packetID = 0;
                connectedPlayers[index].status = PlayerStatus::PLAYER_IDLE;

                std::cout << "CONNECT : new connection " << index << " - " <<
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
        if(connectedPlayers[i].status != PlayerStatus::PLAYER_DISCONNECTED &&
            address == connectedPlayers[i].address &&
            port == connectedPlayers[i].port)
            return true;
    }

    return false;
}

int Server::findConnected(sf::IpAddress address, unsigned short port) {
    for(size_t i = 0; i < connectedPlayers.size(); i++) {
        if(connectedPlayers[i].status != PlayerStatus::PLAYER_DISCONNECTED &&
            address == connectedPlayers[i].address &&
            port == connectedPlayers[i].port)
            return i;
    }
    return -1;
}

void Server::monitorPlayerData() {
    if(game.recieve()) {
        sf::Uint8 state;
        sf::Packet packet;

        int index = findConnected(game.getSender(), game.getSenderPort());
        if (index != -1) {
            sf::Int32 challengeResponse,
                    solution = connectedPlayers[index].seed ^serverSeed;
            game.getRecievedPacket() >> challengeResponse;
            if (challengeResponse == solution) {
                sf::Uint16 pid = 0;
                game.getRecievedPacket() >> pid;

                if (Utils::sequence_greater_than(pid, connectedPlayers[index].packetID)) {
                    connectedPlayers[index].packetID = pid;
                    game.getRecievedPacket() >> connectedPlayers[index].x >> connectedPlayers[index].y;
                }
            }
        }
    }
}

void Server::sendPlayerData() {
    if(serverTick.getElapsedTime().asMilliseconds() > SERVER_TICK_MS) {

        for(int j = 0; j < SERVER_NB_MAX_LOBBY; j++) {
            if(lobbies[j].status == LobbyStatus::LOBBY_PLAYING) {
                sf::Packet packet;

                sf::Uint8 state = 0;
                packet << state;

                for(sf::Uint8 i = 0; i < NB_MAX_JOUEURS; i++) {
                    if(lobbies[j].players[i] != nullptr) {
                        bool connected = lobbies[j].players[i]->status == PlayerStatus::PLAYER_PLAYING;
                        packet << connected << lobbies[j].players[i]->x << lobbies[j].players[i]->y;
                    }
                    else {
                        sf::Int32 err = 0;
                        packet << false << err << err;
                    }

                }

                for(sf::Uint8  i = 0; i < NB_MAX_JOUEURS; i++) {
                    if(lobbies[j].players[i] != nullptr && lobbies[j].players[i]->status != PlayerStatus::PLAYER_DISCONNECTED) {
                        game.send(packet, lobbies[j].players[i]->address, lobbies[j].players[i]->port);
                    }
                }
            }
        }

        serverTick.restart();
    }

}

int Server::findFistAvailableConnected() {
    for(int i = 0; i< connectedPlayers.size(); i++) {
        if(connectedPlayers[i].status == PlayerStatus::PLAYER_DISCONNECTED)
            return i;
    }
    return -1;
}

void Server::monitorLobby() {
    if (lobby.recieve()) {
        sf::Uint8 state;
        sf::Packet packet;

        lobby.getRecievedPacket() >> state;
        int index = findConnected(lobby.getSender(), lobby.getSenderPort());


        if (index != -1) {
            sf::Int32 challengeResponse,
                    solution = connectedPlayers[index].seed ^serverSeed;
            lobby.getRecievedPacket() >> challengeResponse;


            if (challengeResponse == solution) {
                if (state == 10) { // Create new room
                    if(connectedPlayers[index].status == PlayerStatus::PLAYER_IDLE) {
                        int lobbyIndex = findFirstAvailableLobby(lobbies);
                        if(lobbyIndex != -1) {
                            std::string lobbyName;
                            lobby.getRecievedPacket() >> lobbyName;
                            lobbies[lobbyIndex].status = LobbyStatus::LOBBY_FILLING;
                            lobbies[lobbyIndex].players[0] = &connectedPlayers[index];
                            lobbies[lobbyIndex].name = lobbyName;
                            lobbies[lobbyIndex].limit = NB_MAX_JOUEURS;
                            lobbies[lobbyIndex].nbIn = 1;

                            connectedPlayers[index].status = PlayerStatus::PLAYER_WAITING;

                            sf::Uint32 randID = Random::randint(0, 100000);
                            std::string lobbyID = std::to_string(randID);
                            lobbyID = Utils::paddLeft(lobbyID, 5, '0');
                            lobbies[lobbyIndex].id = lobbyID;


                            std::cout << "LOBBY : new lobby " <<
                                      lobbies[lobbyIndex].id << " - " << lobbies[lobbyIndex].name <<
                                      " " << lobbies[lobbyIndex].players[0]->name << std::endl;

                            packet << state << lobbyID;
                            lobby.send(packet, lobby.getSender(), lobby.getSenderPort());
                        }
                        else
                            state = 100;
                    }
                    else
                        state = 100;

                }
                else if(state == 11) { // Join room
                    std::string lobbyID;
                    lobby.getRecievedPacket() >> lobbyID;

                    int lobbyIndex = findLobbyById(lobbies, lobbyID);

                    if(lobbyIndex < SERVER_NB_MAX_LOBBY && lobbyIndex >= 0 &&
                       lobbies[lobbyIndex].status == LobbyStatus::LOBBY_FILLING) {
                        int playerIndex = findFirstAvailablePlayerSpot(lobbies, lobbyIndex);
                        if(lobbyIndex != -1) {
                            lobbies[lobbyIndex].players[playerIndex] = &connectedPlayers[index];
                            lobbies[lobbyIndex].nbIn++;

                            connectedPlayers[index].status = PlayerStatus::PLAYER_WAITING;

                            std::cout << "LOBBY : " << lobbies[lobbyIndex].players[playerIndex]->name << " joined " <<
                                      lobbies[lobbyIndex].id << std::endl;

                            state = 32;
                            packet << state;
                            lobby.send(packet, lobby.getSender(), lobby.getSenderPort());

                            sendRoomLobbyNotif(lobbyIndex, state, 0);
                        }
                        else
                            state = 100;

                    }
                    else
                        state = 100;

                }
                else if(state == 12) { // Disconnect
                    std::string lobbyID;
                    lobby.getRecievedPacket() >> lobbyID;
                    int lobbyIndex = findLobbyById(lobbies, lobbyID);

                    if(lobbyIndex < SERVER_NB_MAX_LOBBY && lobbyIndex >= 0 &&
                            lobbies[lobbyIndex].status == LobbyStatus::LOBBY_FILLING) {

                        int indPlayer = findPlayerInLobby(lobbies, lobbyIndex, lobby.getSender(), lobby.getSenderPort());
                        if(indPlayer != -1) {

                            std::cout << "LOBBY : " << lobbies[lobbyIndex].players[indPlayer]->name << " quitted " <<
                                      lobbies[lobbyIndex].id << std::endl;

                            lobbies[lobbyIndex].players[indPlayer]->status = PlayerStatus::PLAYER_IDLE;
                            lobbies[lobbyIndex].players[indPlayer] = nullptr;
                            lobbies[lobbyIndex].nbIn--;

                            if(lobbies[lobbyIndex].nbIn <= 0) {
                                std::cout << "LOBBY : " << lobbies[lobbyIndex].name << " closed " <<
                                          lobbies[lobbyIndex].id << std::endl;

                                lobbies[lobbyIndex].status = LobbyStatus::LOBBY_AVAILABLE;
                                lobbies[lobbyIndex].nbIn = 0;
                                state = 50;
                            }
                            else {
                                if(indPlayer == 0)
                                    state = 31;
                                else
                                    state = 32;
                            }

                            packet << state;
                            lobby.send(packet, lobby.getSender(), lobby.getSenderPort());
                            if(state != 50)
                                sendRoomLobbyNotif(lobbyIndex, state, 0);
                        }
                        else
                            state = 100;
                    }
                    else
                        state = 100;
                }
                else if(state == 20) { //Launch game
                    std::string lobbyID;
                    lobby.getRecievedPacket() >> lobbyID;

                    int lobbyIndex = findLobbyById(lobbies, lobbyID);

                    if(lobbyIndex < SERVER_NB_MAX_LOBBY && lobbyIndex >= 0 /*&&
                       lobbies[lobbyIndex].nbIn == lobbies[lobbyIndex].limit*/) {

                        lobbies[lobbyIndex].status = LobbyStatus::LOBBY_PLAYING;
                        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
                            if(lobbies[lobbyIndex].players[i] != nullptr)
                                lobbies[lobbyIndex].players[i]->status = PlayerStatus::PLAYER_PLAYING;
                        }

                        lobbies[lobbyIndex].load("Beatmaps/1772712 DECO 27 - Ai Kotoba IV feat. Hatsune Miku/[2P] DECO27 - Ai Kotoba IV feat. Hatsune Miku.mm");
                        lobbies[lobbyIndex].startGame();

                        std::cout << "LOBBY : Game launched in lobby " << lobbies[lobbyIndex].id << std::endl<< std::endl;

                        state = 30;
                        packet << state;
                        lobby.send(packet, lobby.getSender(), lobby.getSenderPort());
                        sendRoomLobbyNotif(lobbyIndex, state, 1);
                    }
                    else
                        state = 100;
                }
                else if(state == 21) { //Stop game
                    std::string lobbyID;
                    lobby.getRecievedPacket() >> lobbyID;

                    int lobbyIndex = findLobbyById(lobbies, lobbyID);

                    if(lobbyIndex < SERVER_NB_MAX_LOBBY && lobbyIndex >= 0 &&
                        lobbies[lobbyIndex].status == LobbyStatus::LOBBY_PLAYING) {

                        lobbies[lobbyIndex].status = LobbyStatus::LOBBY_FILLING;
                        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
                            if(lobbies[lobbyIndex].players[i] != nullptr)
                                lobbies[lobbyIndex].players[i]->status = PlayerStatus::PLAYER_WAITING;
                        }

                        std::cout << "LOBBY : Game stopped in lobby " << lobbies[lobbyIndex].id << std::endl<< std::endl;

                        state = 33;
                        packet << state;
                        lobby.send(packet, lobby.getSender(), lobby.getSenderPort());
                        sendRoomLobbyNotif(lobbyIndex, state, 1);
                    }
                    else
                        state = 100;
                }
                else if(state == 22) { //Pause game
                    std::string lobbyID;
                    lobby.getRecievedPacket() >> lobbyID;

                    int lobbyIndex = findLobbyById(lobbies, lobbyID);

                    if(lobbyIndex < SERVER_NB_MAX_LOBBY && lobbyIndex >= 0 &&
                       lobbies[lobbyIndex].status == LobbyStatus::LOBBY_PLAYING) {

                        std::cout << "LOBBY : Game paused in lobby " << lobbies[lobbyIndex].id << std::endl<< std::endl;

                        state = 34;
                        packet << state;
                        lobby.send(packet, lobby.getSender(), lobby.getSenderPort());
                        sendRoomLobbyNotif(lobbyIndex, state, 1);
                    }
                    else
                        state = 100;
                }
                else if(state == 23) { //Resume game
                    std::string lobbyID;
                    lobby.getRecievedPacket() >> lobbyID;

                    int lobbyIndex = findLobbyById(lobbies, lobbyID);

                    if(lobbyIndex < SERVER_NB_MAX_LOBBY && lobbyIndex >= 0 &&
                       lobbies[lobbyIndex].status == LobbyStatus::LOBBY_PLAYING) {

                        std::cout << "LOBBY : Game resume in lobby " << lobbies[lobbyIndex].id << std::endl<< std::endl;

                        lobbies[lobbyIndex].startGame();

                        state = 35;
                        packet << state;
                        lobby.send(packet, lobby.getSender(), lobby.getSenderPort());
                        sendRoomLobbyNotif(lobbyIndex, state, 1);
                    }
                    else
                        state = 100;
                }
                else if(state == 40) { // Get lobby list

                    packet << state;

                    for(int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
                        sf::Uint8 stat = lobbies[i].status;
                        packet << stat << lobbies[i].id << lobbies[i].name;
                        packet << lobbies[i].nbIn << lobbies[i].limit;
                        if(lobbies[i].status == LobbyStatus::LOBBY_FILLING &&
                        lobbies[i].players[0] != nullptr ) {
                            packet << lobbies[i].players[0]->name;
                        }
                        else {
                            packet << "VIDE";
                        }
                    }

                    lobby.send(packet, lobby.getSender(), lobby.getSenderPort());

                }
                else if(state == 41) { // Get room info
                    std::string lobbyID;
                    lobby.getRecievedPacket() >> lobbyID;
                    int lobbyIndex = findLobbyById(lobbies, lobbyID);
                    if(lobbyIndex < SERVER_NB_MAX_LOBBY && lobbyIndex >= 0 &&
                    lobbies[lobbyIndex].status != LobbyStatus::LOBBY_AVAILABLE) {
                        packet << state << lobbies[lobbyIndex].name << lobbies[lobbyIndex].nbIn << lobbies[lobbyIndex].limit;
                        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
                            if(lobbies[lobbyIndex].players[i] == nullptr)
                                packet << "Vide";
                            else
                                packet << lobbies[lobbyIndex].players[i]->name;
                        }
                        lobby.send(packet, lobby.getSender(), lobby.getSenderPort());
                    }
                    else
                        state = 100;

                }
                else
                    state = 100;
            }
        }

        if(state == 100) { // Unhandled error
            packet << state;
            lobby.send(packet, lobby.getSender(), lobby.getSenderPort());
        }
    }
}


void Server::sendRoomLobbyNotif(int index, sf::Uint8 state, sf::Uint8 param) {

    for(sf::Uint8 i = 0; i < NB_MAX_JOUEURS; i++) {
        if(lobbies[index].players[i] != nullptr) {
            sf::Packet p;
            p << state;
            if(param == 1)
                p << i;
            else
                p << param;
            lobby.send(p, lobbies[index].players[i]->address, lobbies[index].players[i]->port);
        }
    }
}

void Server::updateLobbies(sf::Time elapsed) {
    for(auto & lobbie : lobbies) {
        if(lobbie.status == LOBBY_PLAYING) {
            lobbie.updateGame(elapsed);
            if(lobbie.failed && !lobbie.paused) {
                std::cout << "failed" << std::endl;
                sf::Uint8 state = 34;
                auto checkpoint = lobbie.getCheckpoint();
                sf::Packet p;
                p << state << checkpoint.first << checkpoint.second;
                for(sf::Uint8 i = 0; i < NB_MAX_JOUEURS; i++) {
                    if(lobbie.players[i] != nullptr) {
                        lobby.send(p, lobbie.players[i]->address, lobbie.players[i]->port);
                    }
                }
                lobbie.paused = true;
            }
        }

    }
}


