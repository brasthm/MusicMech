//
// Created by cyril on 13/05/2022.
//

#ifndef MUSICMECH_SERVER_SERVER_H
#define MUSICMECH_SERVER_SERVER_H

#include "UDP_Port.h"
#include "main.h"

#include <vector>
#include <map>


class PlayerInfo {
public:
    inline PlayerInfo() = default;
    inline PlayerInfo(sf::IpAddress a, unsigned short p, sf::Int32 s) {
        address = a;
        port = p;
        seed = s;

        x = 0; y = 0;

        connected = false;
        state = 0;
    };
    inline void clear() {
        address = sf::IpAddress::None;
        port = 0;
        seed = 0;

        x = 0; y = 0;

        connected = false;
        state = 0;
    };

    sf::IpAddress address;
    unsigned short port;
    bool connected;
    sf::Int32 seed, x, y;
    sf::Uint16 packetID;
    sf::Uint8 state;

};

class Server {
private:
    UDP_Port admin, connect, game;
    std::vector<PlayerInfo> connectedPlayers;
    std::map<std::pair<sf::IpAddress, unsigned short>, PlayerInfo> connectionState;
    sf::Int32 serverSeed;
    sf::Clock serverTick;
protected:
    void monitorAdminCommand(bool &loop);
    void monitorConnectRequest();
    void monitorPlayerData();
    void sendPlayerData();
    bool checkConnected(sf::IpAddress address, unsigned short port);
    int findConnected(sf::IpAddress address, unsigned short port);
    int findFistAvailableConnected();

public:
    Server();
    ~Server() = default;

    void run();

};


#endif //MUSICMECH_SERVER_SERVER_H
