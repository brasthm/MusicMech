//
// Created by cyril on 13/05/2022.
//

#ifndef MUSICMECH_SERVER_SERVER_H
#define MUSICMECH_SERVER_SERVER_H

#include "UDP_Port.h"
#include "../main.h"
#include "PlayerInfo.h"
#include "Lobby.h"

#include <vector>
#include <map>



class Server {
private:
    UDP_Port admin, connect, game, lobby;
    std::vector<PlayerInfo> connectedPlayers;
    std::map<std::pair<sf::IpAddress, unsigned short>, PlayerInfo> connectionState;
    std::vector<Lobby> lobbies;
    sf::Int32 serverSeed;
    sf::Clock serverTick;
protected:
    void monitorAdminCommand(bool &loop);
    void monitorConnectRequest();
    void monitorPlayerData();
    void sendPlayerData();
    void monitorLobby();
    void updateLobbies(sf::Time elapsed);


    bool checkConnected(sf::IpAddress address, unsigned short port);
    int findConnected(sf::IpAddress address, unsigned short port);
    int findFistAvailableConnected();

    void sendRoomLobbyNotif(int index, sf::Uint8 state, sf::Uint8 param);

public:
    Server();
    ~Server() = default;

    void run();

};


#endif //MUSICMECH_SERVER_SERVER_H
