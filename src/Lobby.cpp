//
// Created by cyril on 03/06/2022.
//

#include "Lobby.h"

int findFirstAvailableLobby(const std::vector<Lobby> &lobbyList) {
    for(int i = 0; i< SERVER_NB_MAX_LOBBY; i++) {
        if(lobbyList[i].status == LobbyStatus::LOBBY_AVAILABLE)
            return i;
    }

    return -1;
}

int findFirstAvailablePlayerSpot(const std::vector<Lobby> &lobbyList, int indLobby) {
    for(int i = 0; i< NB_MAX_JOUEURS; i++) {
        if(lobbyList[indLobby].players[i] == nullptr)
            return i;
    }
    return -1;
}

int findLobbyById(const std::vector<Lobby> &lobbyList, std::string id) {
    for(int i = 0; i< NB_MAX_JOUEURS; i++) {
        if(lobbyList[i].id == id)
            return i;
    }
    return -1;
}

int findPlayerInLobby(const std::vector<Lobby> &lobbyList, int index, sf::IpAddress address, unsigned short port) {

    for(int i = 0; i < NB_MAX_JOUEURS; i++) {
        if(lobbyList[index].players[i] != nullptr) {
            if(lobbyList[index].players[i]->address == address &&
                    lobbyList[index].players[i]->port == port)
                return i;
        }
    }
    return -1;
}

