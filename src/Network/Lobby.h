//
// Created by cyril on 30/05/2022.
//

#ifndef MUSICMECH_SERVER_LOBBY_H
#define MUSICMECH_SERVER_LOBBY_H

#include <SFML/Network.hpp>
#include <string>

#include "PlayerInfo.h"
#include "../main.h"
#include "../System/Song.h"
#include "../System/Arena.h"
#include "../Entity/EntityManager.h"
#include "../Entity/Totem.h"
#include "../Entity/Joueur.h"
#include "../Mechanics/Mechanic.h"


enum LobbyStatus {
    LOBBY_AVAILABLE,
    LOBBY_FILLING,
    LOBBY_PLAYING

};

class Lobby {

private:
    Song song_;
    sf::Clock timer_;
    sf::Time position_;
    EntityManager manager_;

    std::vector<Totem> totems_;
    std::vector<Joueur> joueurs_;
    std::vector<Mechanic*> mechanics_;

    float currentBeat_;

public:
    inline Lobby() {
        status = LobbyStatus::LOBBY_AVAILABLE;
        limit = nbIn = 0;
        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
            players.emplace_back(nullptr);
            joueurs_.emplace_back();
        }
        for(int i = 0; i < NB_MAX_TOTEM; i++) {
            totems_.emplace_back();
        }

        name = "";
        id = "";

        failed = false;

    };

    std::string name, beatmap, mode;
    LobbyStatus status;
    std::vector<PlayerInfo*> players;
    sf::Uint8 nbIn, limit;
    std::string id;
    bool failed, paused;

    void startGame();
    void updateGame(sf::Time elapsed);
    void load(const std::string &filename);
    std::pair<float, float> getCheckpoint();
    void resetTimer();

};


int findFirstAvailableLobby(const std::vector<Lobby> &lobbyList);
int findFirstAvailablePlayerSpot(const std::vector<Lobby> &lobbyList, int indLobby);
int findLobbyById(const std::vector<Lobby> &lobbyList, std::string id);
int findPlayerInLobby(const std::vector<Lobby> &lobbyList, int index, sf::IpAddress address, unsigned short port);

#endif //MUSICMECH_SERVER_LOBBY_H
