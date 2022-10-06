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
        state = 0;
        color = 0;
        socket = nullptr;

    }
    inline PlayerInfo(sf::IpAddress a, unsigned short p, sf::Int32 s, std::string n) {
        address = a;
        port = p;
        seed = s;

        name = std::move(n);
        packetID = 0;

        x = 0; y = 0;

        status = PlayerStatus::PLAYER_DISCONNECTED;
        state = 0;
        color = 0;
        socket = nullptr;
    };
    inline void clear() {
        address = sf::IpAddress::None;
        port = 0;
        seed = 0;

        x = 0; y = 0;

        status = PlayerStatus::PLAYER_DISCONNECTED;
        state = 0;
        color = 0;
        socket = nullptr;
    };

    sf::IpAddress address;
    unsigned short port;
    sf::Int32 seed, x, y;
    unsigned short udpPort;
    sf::Uint16 packetID;
    sf::Uint8 state;
    std::string name;
    PlayerStatus status;
    sf::Uint32 color;
    TCP_Socket* socket;

};

#endif //MUSICMECH_SERVER_PLAYERINFO_H
