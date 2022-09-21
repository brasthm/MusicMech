//
// Created by cyril on 13/05/2022.
//

#include "Server.h"

#include <SFML/Network.hpp>
#include <chrono>
#include <thread>
#include <iostream>

#include "../System/Random.h"

Server::Server() :  admin_("admin", SERVER_ADMIN_PORT, false),
                    game_("game", SERVER_GAME_PORT, false){
    serverSeed_ = Random::rand();

    for(int i = 0; i < SERVER_NB_MAX_PLAYERS; i++) {
        players_.emplace_back();
    }

    for(int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
        lobbies_.emplace_back();
    }

    connector_.setBlocking(false);
    connector_.listen(SERVER_CONNECT_PORT);
    selector_.add(connector_);
    selector_.add(admin_.getSocket());
    selector_.add(game_.getSocket());
}


void Server::run() {
    serverTick_.restart();

    sf::Clock fps;

    sf::Socket::Status status;
    TCP_Socket* newEntry = nullptr;

    while(!closing_) {
        if (selector_.wait(sf::milliseconds(SERVER_SLEEP))) {
            if (selector_.isReady(connector_)) {
                accepting_ = true;
            }
            if (selector_.isReady(admin_.getSocket())) {
                monitorAdminCommand();
            }
            if (selector_.isReady(game_.getSocket())) {
                monitorPlayerData();
            }
            for (int i = 0; i < clients_.size(); i++) {
                if (selector_.isReady(clients_[i]->getSocket())) {
                    clients_[i]->recieve();
                }
            }
        }

        accept(newEntry);
        for (int i = 0; i < clients_.size(); i++) {
            clients_[i]->monitor();
            monitorClient(i);
        }
        cleanup();
        sendPlayerData();
        
        sf::Time elapsedTime = fps.getElapsedTime();
        fps.restart();

        updateLobbies(elapsedTime);

        if (elapsedTime.asMilliseconds() < SERVER_SLEEP) {
            std::this_thread::sleep_for(std::chrono::milliseconds(SERVER_SLEEP - elapsedTime.asMilliseconds()));
        }        
    }


    selector_.clear();
    connector_.close();
    for (int i = 0; i < clients_.size(); i++) {
        clients_[i]->disconnect();
        delete clients_[i];
    }
    clients_.clear();
}

void Server::accept(TCP_Socket* newEntry)
{
    if (!accepting_)
        return;

    if (!creating_) {
        newEntry = new TCP_Socket();
        creating_ = true;
    }


    sf::Socket::Status status;
    status = connector_.accept(newEntry->getSocket());

    if (status == sf::Socket::Error) {
        std::cout << "TCP_LISTENER (" << connector_.getLocalPort() << ") : Unexpected Error" << std::endl;
        delete newEntry;
        creating_ = false;
        accepting_ = false;
        return;
    }
    if (status == sf::Socket::Disconnected) {
        std::cout << "TCP_LISTENER (" << connector_.getLocalPort() << ") : Port not bound." << std::endl;
        delete newEntry;
        creating_ = false;
        accepting_ = false;
        return;
    }

    if (status == sf::Socket::Done) {
        std::cout << "TCP_LISTENER (" << connector_.getLocalPort() << ") : New connection " << std::endl;
        creating_ = false;
        accepting_ = false;
        newEntry->accept();
        selector_.add(newEntry->getSocket());

        clients_.emplace_back(newEntry);
        return;
    }
}

void Server::cleanup()
{
    for (std::vector<TCP_Socket*>::iterator it = clients_.begin(); it != clients_.end(); ) {
        if ((*it)->isObsolete()) {
            int index = findConnected((*it)->getRemoteAddress(), (*it)->getRemotePort());
            if (index == -1) {
                std::cout << "WARNING : Unable to disconnect properly." << std::endl;
                return;
            }

            for (int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
                if (lobbies_[i].status != LobbyStatus::LOBBY_AVAILABLE) {
                    for (int j = 0; j < NB_MAX_JOUEURS; j++) {
                        if (lobbies_[i].players[j] != nullptr &&
                            lobbies_[i].players[j]->address == players_[index].address &&
                            lobbies_[i].players[j]->port == players_[index].port) {

                            lobbies_[i].players[j] = nullptr;
                            lobbies_[i].nbIn--;

                            sf::Uint8 resstate;

                            if (lobbies_[i].nbIn <= 0) {
                                std::cout << "LOBBY : " << lobbies_[i].name << " closed " <<
                                    lobbies_[i].id << std::endl;

                                lobbies_[i].status = LobbyStatus::LOBBY_AVAILABLE;
                                lobbies_[i].nbIn = 0;
                                resstate = 50;
                            }
                            else {
                                if (j == 0)
                                    resstate = 31;
                                else
                                    resstate = 32;
                            }

                            if (resstate != 50)
                                sendRoomLobbyNotif(i, resstate, 0);
                        }
                    }
                }
            }

            players_[index].clear();

            selector_.remove((*it)->getSocket());
            (*it)->getSocket().disconnect();
            delete* it;
            it = clients_.erase(it);
        }
        else {
            ++it;
        }
    }
}




void Server::monitorAdminCommand() {
    if(admin_.recieve()) {
        std::string cmd;
        admin_.getRecievedPacket() >> cmd;
        std::cout << "ADMIN : " << cmd << std::endl;
        sf::Packet packet;
        if(cmd == "quit") {
            closing_ = false;
            packet << "Server exited";
            admin_.send(packet, admin_.getSender(), admin_.getSenderPort());
        }

        else if(cmd == "name") {
            packet << SERVER_NAME;
            admin_.send(packet, admin_.getSender(), admin_.getSenderPort());
        }
        else if(cmd == "version") {
            packet << SERVER_VERSION;
            admin_.send(packet, admin_.getSender(), admin_.getSenderPort());
        }
        else if(cmd == "NB_CONNECTED") {
            packet << std::to_string(players_.size());
            admin_.send(packet, admin_.getSender(), admin_.getSenderPort());
        }
        else if(cmd == "timeout") {

        }
        else if (cmd == "GOD_MODE") {
            GOD_MODE = !GOD_MODE;
            std::string s = GOD_MODE ? "God mode activated" : "God mode desactivated";
            packet << s;
            admin_.send(packet, admin_.getSender(), admin_.getSenderPort());
        }
        else if(cmd == "PLAYER_LIST") {
            std::string res;

            for(int i = 0; i < players_.size(); i++) {
                if(players_[i].status != PlayerStatus::PLAYER_DISCONNECTED) {
                    res += std::to_string(i) + " - " + players_[i].name + " " +
                        players_[i].address.toString() + ":" +
                            std::to_string(players_[i].port)+"/" + std::to_string(players_[i].udpPort) + "\n";
                    res += "  Status : ";
                    switch(players_[i].status) {
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
                    res += "  - Coords : (" + std::to_string(players_[i].x) +", "
                            + std::to_string(players_[i].y) + ")\n";
                }

            }

            packet << res;
            admin_.send(packet, admin_.getSender(), admin_.getSenderPort());
        }
        else if(cmd == "LOBBY_LIST") {
            std::string res;

            for(int i = 0; i < lobbies_.size(); i++) {
                if(lobbies_[i].status != LobbyStatus::LOBBY_AVAILABLE){
                    res += std::to_string(i) + " - "
                            + lobbies_[i].name + " (" + lobbies_[i].id +")\n";
                    res += " - Filling : " +
                            std::to_string(lobbies_[i].nbIn) + "/" + std::to_string(lobbies_[i].limit);
                    res += " - Status : ";
                    switch(lobbies_[i].status) {
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
                    for(int j= 0; j < lobbies_[i].players.size(); j++) {
                        if(lobbies_[i].players[j] == nullptr)
                            res+="\tVIDE\n";
                        else
                            res+="\t"+lobbies_[i].players[j]->name+"\n";
                    }
                }
            }
            packet << res;
            admin_.send(packet, admin_.getSender(), admin_.getSenderPort());
        }
        else{
            packet << "Command not found";
            admin_.send(packet, admin_.getSender(), admin_.getSenderPort());
        }
    }
}

bool Server::checkConnected(sf::IpAddress address, unsigned short port) {

    for(size_t i = 0; i < players_.size(); i++) {
        if(players_[i].status != PlayerStatus::PLAYER_DISCONNECTED &&
            address == players_[i].address &&
            port == players_[i].port)
            return true;
    }

    return false;
}

void Server::monitorPlayerData() {
    if(game_.recieve()) {
        sf::Uint8 state;
        sf::Packet packet;

        int index = findUDPConnected(game_.getSender(), game_.getSenderPort());
        if (index == -1) {
            std::cout << "GAME PORT : Can't find player (" << game_.getSender().toString() << ":" << (int)game_.getSenderPort() << ")" << std::endl;
            return;
        }

        sf::Int32 challengeResponse,
                solution = players_[index].seed ^serverSeed_;
        game_.getRecievedPacket() >> challengeResponse;

        if (challengeResponse != solution) {
            std::cout << "GAME PORT : Wrong challenge (" << players_[index].name << ")." << std::endl;
            return;
        }

        game_.getRecievedPacket() >> state;

        // Game position
        if (state == 0) {
            sf::Uint16 pid = 0;
            game_.getRecievedPacket() >> pid;

            if (!Utils::sequence_greater_than(pid, players_[index].packetID)) {
                std::cout << "GAME PORT : Outdated packet. (" << players_[index].name << ")." << std::endl;
                return;
            }


            sf::Int32 x, y;
            game_.getRecievedPacket() >> x >> y;


            if (!game_.valid()) {
                std::cout << "GAME PORT : Data corrupted (" << players_[index].name << ")." << std::endl;
                return;
            }

            players_[index].x = x;
            players_[index].y = y;
            players_[index].packetID = pid;

            return;
        }

        if (state == 1) {
            //std::cout << "GAME PORT : Ping Request(" << players_[index].name << ")." << std::endl;
            sf::Packet response;
            sf::Int64 clientTime;

            game_.getRecievedPacket() >> clientTime;

            if (!game_.valid()) {
                std::cout << "GAME PORT : Data corrupted (" << players_[index].name << ")." << std::endl;
                return;
            }

            sf::Int64 serverTime = std::chrono::steady_clock::now().time_since_epoch() / std::chrono::milliseconds(1);


            float beat;
            int lobbyInd = findLobbyContainingPlayer(players_[index].address, players_[index].port);

            if (lobbyInd == -1) {
                beat = 0;
            }
            else {
                beat = lobbies_[lobbyInd].getCurrentBeat();
            }

            response << state << clientTime << serverTime << beat;

            game_.send(response, players_[index].address, players_[index].udpPort);

            return;
        }
        std::cout << "GAME PORT : State unrecognized (" << (int)state << ")." << std::endl;
    }
}

void Server::sendPlayerData() {
    if(serverTick_.getElapsedTime().asMilliseconds() > SERVER_TICK_MS) {

        for(int j = 0; j < SERVER_NB_MAX_LOBBY; j++) {
            if(lobbies_[j].status == LobbyStatus::LOBBY_PLAYING) {
                sf::Packet packet;

                sf::Uint8 state = 0;
                packet << state;

                for(sf::Uint8 i = 0; i < NB_MAX_JOUEURS; i++) {
                    if(lobbies_[j].players[i] != nullptr) {
                        bool connected = lobbies_[j].players[i]->status == PlayerStatus::PLAYER_PLAYING;
                        packet << connected << lobbies_[j].players[i]->x << lobbies_[j].players[i]->y;
                    }
                    else {
                        if (GOD_MODE) {
                            sf::Int32 err = 200 * i + 200;
                            packet << true << err << 100;
                        }
                        else {
                            sf::Int32 err = 0;
                            packet << false << 0 << 0;
                        }
                    }

                }

                for(sf::Uint8  i = 0; i < NB_MAX_JOUEURS; i++) {
                    if(lobbies_[j].players[i] != nullptr && lobbies_[j].players[i]->status != PlayerStatus::PLAYER_DISCONNECTED) {
                        game_.send(packet, lobbies_[j].players[i]->address, lobbies_[j].players[i]->udpPort);
                    }
                }
            }
        }

        serverTick_.restart();
    }

}

int Server::findFistAvailableConnected() {
    for(int i = 0; i< players_.size(); i++) {
        if(players_[i].status == PlayerStatus::PLAYER_DISCONNECTED)
            return i;
    }
    return -1;
}

int Server::findLobbyContainingPlayer(sf::IpAddress address, unsigned short port)
{
    for (int i = 0; i < lobbies_.size(); i++) {
        for (int j = 0; j < NB_MAX_JOUEURS; j++) {
            if (lobbies_[i].players[j] != nullptr && lobbies_[i].players[j]->address == address && lobbies_[i].players[j]->port == port)
                return i;
        }
    }
    return -1;
}

int Server::findConnected(sf::IpAddress address, unsigned short port) {
    for (size_t i = 0; i < players_.size(); i++) {
        if (players_[i].status != PlayerStatus::PLAYER_DISCONNECTED &&
            address == players_[i].address &&
            port == players_[i].port)
            return i;
    }
    return -1;
}

int Server::findUDPConnected(sf::IpAddress address, unsigned short port)
{
    for (size_t i = 0; i < players_.size(); i++) {
        if (players_[i].status != PlayerStatus::PLAYER_DISCONNECTED &&
            address == players_[i].address &&
            port == players_[i].udpPort)
            return i;
    }
    return -1;
}

void Server::monitorClient(int i)
{
    if (!clients_[i]->isReady()) {
        return;
    }

    sf::Packet packet = clients_[i]->getRecivedPacket();

    sf::Uint8 state;
    packet >> state;
    if (!packet) {
        std::cout << "TCP_SOCKET (" << i << ") : Can't read state." << std::endl;
        return;
    }

    // CONNCETION REQUEST
    if (state == 100) {
        sf::String name;
        sf::Int32 seed;
        sf::Uint16 port;
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        packet >> name >> seed >> port;

        if (!packet) {
            std::cout << "100 TCP_SOCKET (" << i << ") : Invalid packet (100)." << std::endl;
            return;
        }

        int index = findFistAvailableConnected();
        if (index == -1) {
            std::cout << "100 TCP_SOCKET (" << i << ") : Player limit reached (" << SERVER_NB_MAX_PLAYERS << ")." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        players_[index].name = name;
        players_[index].seed = seed;
        players_[index].address = clients_[i]->getRemoteAddress();
        players_[index].port = clients_[i]->getRemotePort();
        players_[index].udpPort = port;
        players_[index].status = PlayerStatus::PLAYER_IDLE;
        players_[index].packetID = 0;
        players_[index].socket = clients_[i];

        std::cout << "100 TCP_SOCKET (" << i << ") : New connection." << std::endl;

        responsePacket << state << response << serverSeed_;
        clients_[i]->send(responsePacket);

        return;
    }

    // CHECK CHALLENGE
    if (state == 101) {
        sf::Int32 challengeResponse;
        sf::Packet responsePacket;
        sf::Uint8 response = 0;

        packet >> challengeResponse;

        if (!packet) {
            std::cout << "101 TCP_SOCKET (" << i << ") : Invalid packet (101)." << std::endl;
            clients_[i]->disconnect();
            return;
        }

        int index = findConnected(clients_[i]->getRemoteAddress(), clients_[i]->getRemotePort());
        if (index == -1) {
            std::cout << "101 TCP_SOCKET (" << i << ") : Player not connected." << std::endl;
            clients_[i]->disconnect();
            return;
        }

        sf::Int32 solution = players_[index].seed ^ serverSeed_;

        if (challengeResponse != solution) {
            std::cout << "101 TCP_SOCKET (" << i << ") : Identification Challenge Failed." << std::endl;
            clients_[i]->disconnect();
            return;
        }

        responsePacket << state << response;
        clients_[i]->send(responsePacket);

        std::cout << "101 TCP_SOCKET (" << i << ") : Identified." << std::endl;

        return;
    }

    // DISCONNECTION REQUEST
    if (state == 110) {
        std::cout << "110 TCP_SOCKET (" << i << ") : Disconnected." << std::endl;

        clients_[i]->disconnect();

        return;
    }

    // CREATE LOBBY
    if (state == 10) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        int index = findConnected(clients_[i]->getRemoteAddress(), clients_[i]->getRemotePort());
        if (index == -1) {
            std::cout << "10 TCP_SOCKET (" << i << ") : Player not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        if (players_[index].status != PlayerStatus::PLAYER_IDLE) {
            std::cout << "10 TCP_SOCKET (" << i << ") : " << players_[index].name << " is not idle." << std::endl;
            response = 2;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }


        int lobbyIndex = findFirstAvailableLobby(lobbies_);
        if (lobbyIndex == -1) {
            std::cout << "10 TCP_SOCKET (" << i << ") : Lobby limit reached (" << SERVER_NB_MAX_PLAYERS << ")." << std::endl;
            response = 3;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        sf::String lobbyName, beatmap, mode;
        packet >> lobbyName >> beatmap >> mode;

        if (!packet) {
            std::cout << "10 TCP_SOCKET (" << i << ") : Invalid packet (10)." << std::endl;
            return;
        }

        lobbies_[lobbyIndex].status = LobbyStatus::LOBBY_FILLING;
        lobbies_[lobbyIndex].players[0] = &players_[index];
        lobbies_[lobbyIndex].name = lobbyName;
        lobbies_[lobbyIndex].beatmap = beatmap;
        lobbies_[lobbyIndex].mode = mode;
        lobbies_[lobbyIndex].limit = mode == "2P" ? 2 : NB_MAX_JOUEURS;
        lobbies_[lobbyIndex].nbIn = 1;

        players_[index].status = PlayerStatus::PLAYER_WAITING;

        sf::Uint32 randID = Random::randint(0, 100000);
        std::string lobbyID = std::to_string(randID);
        lobbyID = Utils::paddLeft(lobbyID, 5, '0');
        lobbies_[lobbyIndex].id = lobbyID;

        response = 0;
        responsePacket << state << response << sf::String(lobbyID);

        clients_[i]->send(responsePacket);

        std::cout << "LOBBY : new lobby " <<
            lobbies_[lobbyIndex].id << " - " << lobbies_[lobbyIndex].name <<
            " " << lobbies_[lobbyIndex].players[0]->name << std::endl;

        return;
        
    }

    // JOIN LOBBY
    if (state == 11) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        int index = findConnected(clients_[i]->getRemoteAddress(), clients_[i]->getRemotePort());
        if (index == -1) {
            std::cout << "11 TCP_SOCKET (" << i << ") : Player not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        sf::String lobbyID;
        packet >> lobbyID;

        if (!packet) {
            std::cout << "11 TCP_SOCKET (" << i << ") : Invalid packet (11)." << std::endl;
            return;
        }

        int lobbyIndex = findLobbyById(lobbies_, lobbyID);

        if (lobbyIndex == -1) {
            std::cout << "11 TCP_SOCKET (" << i << ") : Lobby not found." << std::endl;
            response = 2;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        if (lobbies_[lobbyIndex].status != LobbyStatus::LOBBY_FILLING) {
            std::cout << "11 TCP_SOCKET (" << i << ") : " << lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ") is not in ready." << std::endl;
            response = 3;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        int playerIndex = findFirstAvailablePlayerSpot(lobbies_, lobbyIndex);
        if (lobbyIndex == -1) {
            std::cout << "11 TCP_SOCKET (" << i << ") : Room is full" << std::endl;
            response = 4;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        lobbies_[lobbyIndex].players[playerIndex] = &players_[index];
        lobbies_[lobbyIndex].nbIn++;

        players_[index].status = PlayerStatus::PLAYER_WAITING;

        std::cout << "LOBBY : " << lobbies_[lobbyIndex].players[playerIndex]->name << " joined " <<
            lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ")" << std::endl;

        sf::Uint8 resstate = 32;
        responsePacket << state << response << (sf::Int32)playerIndex;

        clients_[i]->send(responsePacket);

        sendRoomLobbyNotif(lobbyIndex, resstate, 0);

        return;
    }


    // QUIT LOBBY

    if (state == 12) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        sf::String lobbyID;
        packet >> lobbyID;

        if (!packet) {
            std::cout << "12 TCP_SOCKET (" << i << ") : Invalid packet (12)." << std::endl;
            return;
        }

        int lobbyIndex = findLobbyById(lobbies_, lobbyID);

        if (lobbyIndex == -1) {
            std::cout << "12 TCP_SOCKET (" << i << ") : Lobby not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        /*if (lobbies_[lobbyIndex].status != LobbyStatus::LOBBY_FILLING) {
            std::cout << "12 TCP_SOCKET (" << i << ") : " << lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ") is not in ready." << std::endl;
            response = 2;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }*/

        int indPlayer = findPlayerInLobby(lobbies_, lobbyIndex, clients_[i]->getRemoteAddress(), clients_[i]->getRemotePort());
        if (indPlayer == -1) {
            std::cout << "12 TCP_SOCKET (" << i << ") : Player not found." << std::endl;
            response = 3;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        std::cout << "LOBBY : " << lobbies_[lobbyIndex].players[indPlayer]->name << " quitted " <<
            lobbies_[lobbyIndex].id << std::endl;

        lobbies_[lobbyIndex].players[indPlayer]->status = PlayerStatus::PLAYER_IDLE;
        lobbies_[lobbyIndex].players[indPlayer] = nullptr;
        lobbies_[lobbyIndex].nbIn--;


        sf::Uint8 resstate;

        if (lobbies_[lobbyIndex].nbIn <= 0) {
            std::cout << "LOBBY : " << lobbies_[lobbyIndex].name << " closed " <<
                lobbies_[lobbyIndex].id << std::endl;

            lobbies_[lobbyIndex].status = LobbyStatus::LOBBY_AVAILABLE;
            lobbies_[lobbyIndex].nbIn = 0;
            resstate = 50;
        }
        else {
            if (indPlayer == 0)
                resstate = 31;
            else
                resstate = 32;
        }

        responsePacket << state << response << resstate;
        clients_[i]->send(responsePacket);

        if(resstate != 50)
            sendRoomLobbyNotif(lobbyIndex, resstate, 0);

        return;
    }

    // GAME START
    if (state == 20) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        sf::String lobbyID;
        packet >> lobbyID;

        if (!packet) {
            std::cout << "20 TCP_SOCKET (" << i << ") : Invalid packet (20)." << std::endl;
            return;
        }

        int lobbyIndex = findLobbyById(lobbies_, lobbyID);

        if (lobbyIndex == -1) {
            std::cout << "20 TCP_SOCKET (" << i << ") : Lobby not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }
        
        
        /*if (lobbies_[lobbyIndex].nbIn == lobbies_[lobbyIndex].limit) {
            std::cout << "20 TCP_SOCKET (" << i << ") : " << lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ") is not filled. Game not started." << std::endl;
            response = 2;
            responsePacket << response;
            clients_[i]->send(responsePacket);
            return;
        }*/

        bool good = true;
        for (int j = 0; j < lobbies_[lobbyIndex].nbIn; j++) {
            good = good && lobbies_[lobbyIndex].players[j]->status == PlayerStatus::PLAYER_READY;
        }
        good = true;
        if (!good) {
            std::cout << "20 TCP_SOCKET (" << i << ") : Players in " << lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ") are not ready. Game not started." << std::endl;
            response = 3;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        lobbies_[lobbyIndex].status = LobbyStatus::LOBBY_PLAYING;
        for (int j = 0; j < NB_MAX_JOUEURS; j++) {
            if (lobbies_[lobbyIndex].players[j] != nullptr)
                lobbies_[lobbyIndex].players[j]->status = PlayerStatus::PLAYER_PLAYING;
        }

        songs_.setSelectedById(lobbies_[lobbyIndex].beatmap);
        songs_.setMode(lobbies_[lobbyIndex].mode);

        lobbies_[lobbyIndex].load(songs_.getSelectedPath());
        lobbies_[lobbyIndex].resetTimer();
        lobbies_[lobbyIndex].startGame();

        std::cout << "LOBBY : Game launched in lobby " << lobbies_[lobbyIndex].id << std::endl;

        sf::Uint8 resstate = 30;
        responsePacket << state << response;

        clients_[i]->send(responsePacket);
        
        sendRoomLobbyNotif(lobbyIndex, resstate, 1);
        return;
    }

    // GAME STOP
    if (state == 21) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        sf::String lobbyID;
        packet >> lobbyID;

        if (!packet) {
            std::cout << "21 TCP_SOCKET (" << i << ") : Invalid packet (21)." << std::endl;
            return;
        }

        int lobbyIndex = findLobbyById(lobbies_, lobbyID);

        if (lobbyIndex == -1) {
            std::cout << "21 TCP_SOCKET (" << i << ") : Lobby not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        if (lobbies_[lobbyIndex].status != LobbyStatus::LOBBY_PLAYING) {
            std::cout << "21 TCP_SOCKET (" << i << ") : " << lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ") is not playing." << std::endl;
            response = 2;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        lobbies_[lobbyIndex].status = LobbyStatus::LOBBY_FILLING;
        for (int j = 0; j < NB_MAX_JOUEURS; j++) {
            if (lobbies_[lobbyIndex].players[j] != nullptr)
                lobbies_[lobbyIndex].players[j]->status = PlayerStatus::PLAYER_WAITING;
        }

        std::cout << "LOBBY : Game stopped in lobby " << lobbies_[lobbyIndex].id << std::endl;

        sf::Uint8 resstate = 33;
        responsePacket << state << response;
        clients_[i]->send(responsePacket);
        sendRoomLobbyNotif(lobbyIndex, resstate, 1);

        return;
    }

    // GAME PAUSE
    if (state == 22) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        sf::String lobbyID;
        packet >> lobbyID;

        if (!packet) {
            std::cout << "22 TCP_SOCKET (" << i << ") : Invalid packet (22)." << std::endl;
            return;
        }

        int lobbyIndex = findLobbyById(lobbies_, lobbyID);

        if (lobbyIndex == -1) {
            std::cout << "22 TCP_SOCKET (" << i << ") : Lobby not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        if (lobbies_[lobbyIndex].status != LobbyStatus::LOBBY_PLAYING) {
            std::cout << "22 TCP_SOCKET (" << i << ") : " << lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ") is not playing." << std::endl;
            response = 2;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        std::cout << "LOBBY : Game paused in lobby " << lobbies_[lobbyIndex].id << std::endl;

        sf::Uint8 resstate = 34;
        responsePacket << state << response;
        clients_[i]->send(responsePacket);
        sendRoomLobbyNotif(lobbyIndex, resstate, 1);

        return;
    }

    // RESUME GAME
    if (state == 23) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        sf::String lobbyID;
        packet >> lobbyID;

        if (!packet) {
            std::cout << "23 TCP_SOCKET (" << i << ") : Invalid packet (23)." << std::endl;
            return;
        }

        int lobbyIndex = findLobbyById(lobbies_, lobbyID);

        if (lobbyIndex == -1) {
            std::cout << "23 TCP_SOCKET (" << i << ") : Lobby not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        if (lobbies_[lobbyIndex].status != LobbyStatus::LOBBY_PLAYING) {
            std::cout << "23 TCP_SOCKET (" << i << ") : " << lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ") is not playing." << std::endl;
            response = 2;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        std::cout << "LOBBY : Game resume in lobby " << lobbies_[lobbyIndex].id << std::endl;

        lobbies_[lobbyIndex].startGame();

        sf::Uint8 resstate = 35;
        responsePacket << state << response;
        clients_[i]->send(responsePacket);
        sendRoomLobbyNotif(lobbyIndex, resstate, 1);

        return;
    }

    // LOBBY READY
    if (state == 24) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        sf::String lobbyID;
        packet >> lobbyID;

        if (!packet) {
            std::cout << "24 TCP_SOCKET (" << i << ") : Invalid packet (24)." << std::endl;
            return;
        }

        int lobbyIndex = findLobbyById(lobbies_, lobbyID);


        if (lobbyIndex == -1) {
            std::cout << "24 TCP_SOCKET (" << i << ") : Lobby not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        if (lobbies_[lobbyIndex].status != LobbyStatus::LOBBY_FILLING) {
            std::cout << "24 TCP_SOCKET (" << i << ") : " << lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ") is not filling." << std::endl;
            response = 2;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        int sender = findPlayerInLobby(lobbies_, lobbyIndex, clients_[i]->getRemoteAddress(), clients_[i]->getRemotePort());

        if (sender == -1) {
            std::cout << "24 TCP_SOCKET (" << i << ") : Player not found." << std::endl;
            response = 3;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }
        sf::Uint32 color;
        packet >> color;
        
        if (!packet) {
            std::cout << "24 TCP_SOCKET (" << i << ") : Invalid packet (color)." << std::endl;
            return;
        }

        lobbies_[lobbyIndex].players[sender]->color = color;
        if (lobbies_[lobbyIndex].players[sender]->status == PlayerStatus::PLAYER_READY) {
            lobbies_[lobbyIndex].players[sender]->status = PlayerStatus::PLAYER_WAITING;
            std::cout << "LOBBY : " << lobbies_[lobbyIndex].players[sender]->name << " is no longer ready in " << lobbies_[lobbyIndex].id << std::endl;
        }
        else {
            lobbies_[lobbyIndex].players[sender]->status = PlayerStatus::PLAYER_READY;
            std::cout << "LOBBY : " << lobbies_[lobbyIndex].players[sender]->name << " is ready in " << lobbies_[lobbyIndex].id << std::endl;
        }

        sf::Uint8 resstate = 32;
        responsePacket << state << response;
        clients_[i]->send(responsePacket);
        sendRoomLobbyNotif(lobbyIndex, resstate, 1);

        return;
    }

    // CHANGE BEATMAP
    if (state == 25) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        sf::String lobbyID;
        packet >> lobbyID;

        

        if (!packet) {
            std::cout << "25 TCP_SOCKET (" << i << ") : Invalid packet (25)." << std::endl;
            return;
        }

        int lobbyIndex = findLobbyById(lobbies_, lobbyID);


        if (lobbyIndex == -1) {
            std::cout << "25 TCP_SOCKET (" << i << ") : Lobby not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        if (lobbies_[lobbyIndex].status != LobbyStatus::LOBBY_FILLING) {
            std::cout << "25 TCP_SOCKET (" << i << ") : " << lobbies_[lobbyIndex].name << "(" << lobbies_[lobbyIndex].id << ") is not in ready." << std::endl;
            response = 2;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        sf::String beatmap, mode;

        packet >> beatmap >> mode;

        if (!packet) {
            std::cout << "25 TCP_SOCKET (" << i << ") : Invalid packet (25)." << std::endl;
            return;
        }

        lobbies_[lobbyIndex].beatmap = beatmap;
        lobbies_[lobbyIndex].mode = mode;

        std::cout << "LOBBY : Beatmap changed to [" << lobbies_[lobbyIndex].beatmap << "] " <<
            lobbies_[lobbyIndex].mode << " in lobby " << lobbies_[lobbyIndex].id << std::endl;

        for (int j = 0; j < lobbies_[lobbyIndex].limit; j++) {
            if (lobbies_[lobbyIndex].players[j] != nullptr)
                lobbies_[lobbyIndex].players[j]->status = PlayerStatus::PLAYER_WAITING;
        }

        if (lobbies_[lobbyIndex].mode == "2P" && lobbies_[lobbyIndex].limit > 2) {
            sf::Packet p;
            sf::Uint8 data = 31;
            p << data;
            for (int j = 2; j < lobbies_[lobbyIndex].limit; j++) {
                if (lobbies_[lobbyIndex].players[j] != nullptr && lobbies_[lobbyIndex].players[j]->socket != nullptr) {
                    lobbies_[lobbyIndex].players[j]->socket->send(p); 
                }
            }
            lobbies_[lobbyIndex].limit = 2;
        }
        else if (lobbies_[lobbyIndex].mode == "4P" && lobbies_[lobbyIndex].limit < 4) {
            lobbies_[lobbyIndex].limit = 4;
        }

        sf::Uint8 resstate = 32;
        responsePacket << state << response;
        clients_[i]->send(responsePacket);
        sendRoomLobbyNotif(lobbyIndex, resstate, 1);

        return;
    }

    // GET LOBBY LIST

    if (state == 40) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        responsePacket << state;

        for (int j = 0; j < SERVER_NB_MAX_LOBBY; j++) {
            sf::Uint8 stat = lobbies_[j].status;
            responsePacket << stat << sf::String(lobbies_[j].id) << sf::String(lobbies_[j].name);
            responsePacket << lobbies_[j].nbIn << lobbies_[j].limit;
            if (lobbies_[j].status == LobbyStatus::LOBBY_FILLING &&
                lobbies_[j].players[0] != nullptr) {
                responsePacket << sf::String(lobbies_[j].players[0]->name);
            }
            else {
                responsePacket << sf::String("VIDE");
            }
        }

        clients_[i]->send(responsePacket);

        return;
    }

    if (state == 41) {
        sf::Uint8 response = 0;
        sf::Packet responsePacket;

        std::string lobbyID;
        packet >> lobbyID;

        if (!packet) {
            std::cout << "41 TCP_SOCKET (" << i << ") : Invalid packet (41)." << std::endl;
            return;
        }

        int lobbyIndex = findLobbyById(lobbies_, lobbyID);


        if (lobbyIndex == -1) {
            std::cout << "41 TCP_SOCKET (" << i << ") : Lobby not found." << std::endl;
            response = 1;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        if (lobbies_[lobbyIndex].status == LobbyStatus::LOBBY_AVAILABLE) {
            std::cout << "41 TCP_SOCKET (" << i << ") : Requested lobby is not in initialized." << std::endl;
            response = 2;
            responsePacket << state << response;
            clients_[i]->send(responsePacket);
            return;
        }

        responsePacket << state <<
            sf::String(lobbies_[lobbyIndex].name) <<
            lobbies_[lobbyIndex].nbIn <<
            lobbies_[lobbyIndex].limit <<
            sf::String(lobbies_[lobbyIndex].beatmap) <<
            sf::String(lobbies_[lobbyIndex].mode);

        for (int i = 0; i < NB_MAX_JOUEURS; i++) {
            if (lobbies_[lobbyIndex].players[i] == nullptr)
                responsePacket << (sf::Uint8)PlayerStatus::PLAYER_DISCONNECTED << sf::String("") << sf::Uint32(0);
            else
                responsePacket << (sf::Uint8)lobbies_[lobbyIndex].players[i]->status << sf::String(lobbies_[lobbyIndex].players[i]->name)
                << lobbies_[lobbyIndex].players[i]->color;
        }

        clients_[i]->send(responsePacket);

        return;
    }

    std::cout << "TCP_SOCKET (" << i << ") : Unrecognized message (" << state << ")." << std::endl;
}

void Server::sendRoomLobbyNotif(int index, sf::Uint8 state, sf::Uint8 param) {

    for (sf::Uint8 i = 0; i < NB_MAX_JOUEURS; i++) {
        if (lobbies_[index].players[i] != nullptr) {
            sf::Packet p;
            p << state;
            if (param == 1) p << i;
            else p << param;

            if (lobbies_[index].players[i]->socket != nullptr)
                lobbies_[index].players[i]->socket->send(p);
            else
                std::cout << "Lobby " << lobbies_[index].name << "(" << lobbies_[index].id << ") : Player "
                << lobbies_[index].players[i]->name << " is not bound to a socket. Packet not sent." << std::endl;
        }
    }
}


void Server::updateLobbies(sf::Time elapsed) {
    for(auto & lobbie : lobbies_) {
        if(lobbie.status == LOBBY_PLAYING) {
            lobbie.updateGame(elapsed);
            if(lobbie.failed && !lobbie.paused) {
                std::cout << "failed" << std::endl;
                sf::Uint8 state = 34;
                auto checkpoint = lobbie.getCheckpoint();
                sf::Packet p;
                p << state << checkpoint.first << checkpoint.second;
                for(sf::Uint8 i = 0; i < NB_MAX_JOUEURS; i++) {
                    if(lobbie.players[i] != nullptr && lobbie.players[i]->socket != nullptr) {
                        lobbie.players[i]->socket->send(p);
                    }
                }
                lobbie.paused = true;
            }
        }

    }
}


