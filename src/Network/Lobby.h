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
    LOBBY_PLAYING,
    LOBBY_STARTING

};

class Lobby {

private:
    Song song_;
    sf::Time position_;
    EntityManager manager_;

    std::vector<Totem> totems_;
    std::vector<Joueur> joueurs_;
    std::vector<Mechanic*> mechanics_;

    float currentBeat_;
    int currentSection_ = 0;

    Arena arena_;

public:
    Lobby();
    ~Lobby();

    Lobby(const Lobby&) = default;
    Lobby& operator=(const Lobby&) = default;

    std::string name, beatmap;
    LobbyStatus status;
    std::vector<PlayerInfo*> players;
    sf::Uint8 nbIn, limit;
    sf::Uint64 startingTime;
    std::string id;
    bool failed, paused;

    void startGame();
    void updateGame(sf::Time elapsed);
    void load(const std::string &filename);
    std::pair<float, float> getCheckpoint();
    void resetTimer();
    float getCurrentBeat();
    float getPosition();
    void setStatusPacket(sf::Packet & packet);
    void setPlayer(int i, std::string name, sf::Uint32 color);
    void computeSequences();
    void setRandomSequence(sf::Packet& packet);
};


int findFirstAvailableLobby(const std::vector<Lobby> &lobbyList);
int findFirstAvailablePlayerSpot(const std::vector<Lobby> &lobbyList, int indLobby);
int findLobbyById(const std::vector<Lobby> &lobbyList, std::string id);
int findPlayerInLobby(const std::vector<Lobby> &lobbyList, int index, sf::IpAddress address, unsigned short port);

#endif //MUSICMECH_SERVER_LOBBY_H
