//
// Created by cyril on 30/05/2022.
//

#ifndef MUSICMECH_SERVER_PLAYERINFO_H
#define MUSICMECH_SERVER_PLAYERINFO_H

#include <SFML/Network.hpp>
#include <utility>

#include "TCP_Socket.h"

enum PlayerStatus {
    PLAYER_DISCONNECTED, PLAYER_IDLE, PLAYER_WAITING, PLAYER_READY, PLAYER_PLAYING
};

class PlayerInfo {
public:
    inline PlayerInfo() {
        address = sf::IpAddress::None;
        port = 0;
        seed = 0;

        name = "";
        packetID = 0;

        x = 0; y = 0;

        status = PlayerStatus::PLAYER_DISCONNECTED;
        id = 0;
        state = 0;
        color = 0;
        socket = nullptr;

        bannerID = 1;
        titleID = 0;

    }
    inline PlayerInfo(sf::IpAddress a, unsigned short p, sf::Int32 s, std::string n, sf::Int32 b, sf::Int32 t) {
        address = a;
        port = p;
        seed = s;

        name = std::move(n);
        packetID = 0;

        x = 0; y = 0;

        status = PlayerStatus::PLAYER_DISCONNECTED;
        id = 0;
        state = 0;
        color = 0;
        socket = nullptr;

        bannerID = b;
        titleID = t;
    };
    inline void clear() {
        address = sf::IpAddress::None;
        port = 0;
        seed = 0;

        x = 0; y = 0;

        status = PlayerStatus::PLAYER_DISCONNECTED;
        id = 0;
        state = 0;
        color = 0;
        socket = nullptr;
        bannerID = 1;
        titleID = 0;
    };

    sf::IpAddress address;
    unsigned short port;
    sf::Int32 seed, x, y, bannerID, titleID;
    unsigned short udpPort;
    sf::Uint16 packetID;
    sf::Uint8 state;
    std::string name;
    PlayerStatus status;
    sf::Uint32 color;
    TCP_Socket* socket;
    sf::Uint32 id;

};

#endif //MUSICMECH_SERVER_PLAYERINFO_H
