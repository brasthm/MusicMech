//
// Created by cyril on 30/05/2022.
//

#ifndef MUSICMECH_SERVER_LOBBY_H
#define MUSICMECH_SERVER_LOBBY_H

#include <SFML/Network.hpp>
#include <string>

#include "PlayerInfo.h"
#include "../main.h"

enum LobbyStatus {
    LOBBY_AVAILABLE,
    LOBBY_FILLING,
    LOBBY_PLAYING

};

class Lobby {
public:
    inline Lobby() {
        status = LobbyStatus::LOBBY_AVAILABLE;
        limit = nbIn = 0;
        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
            players.emplace_back(nullptr);
        }
        name = "";

        id = "";
    };

    std::string name;
    LobbyStatus status;
    std::vector<PlayerInfo*> players;
    sf::Uint8 nbIn, limit;
    std::string id;

};


int findFirstAvailableLobby(const std::vector<Lobby> &lobbyList);
int findFirstAvailablePlayerSpot(const std::vector<Lobby> &lobbyList, int indLobby);
int findLobbyById(const std::vector<Lobby> &lobbyList, std::string id);
int findPlayerInLobby(const std::vector<Lobby> &lobbyList, int index, sf::IpAddress address, unsigned short port);

#endif //MUSICMECH_SERVER_LOBBY_H
