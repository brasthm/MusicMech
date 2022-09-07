//
// Created by cyril on 03/06/2022.
//

#include "Lobby.h"

#include <iostream>

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
    for(int i = 0; i< SERVER_NB_MAX_LOBBY; i++) {
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

void Lobby::startGame() {
    manager_.clear();
    for(int i = 0; i < NB_MAX_JOUEURS; i++) {
        manager_.addPlayer(std::addressof(joueurs_[i]));
    }
    for(int i = 0; i < NB_MAX_TOTEM; i++) {
        manager_.addTotem(std::addressof(totems_[i]));
    }

    failed = false;
    paused = false;
    timer_.restart();
    auto check = getCheckpoint();
    position_ = sf::seconds(check.first);
    currentBeat_ = check.second;
    std::cout << "Position : " << position_.asSeconds() << " Current Beat : " << currentBeat_ << std::endl;

    for(auto & i : mechanics_) {
        i->reset(currentBeat_);
    }
    for(auto & totem:totems_) {
        totem.setActive(false);
    }
    for(auto & joueur:joueurs_) {
        joueur.reset();
    }
    for(int i = 0; i < players.size(); i++) {
        if(players[i] != nullptr)
            joueurs_[i].setActive(true);
    }
}

void Lobby::updateGame(sf::Time elapsed) {
    if(!paused) {
        position_ += timer_.getElapsedTime();
        timer_.restart();
        currentBeat_ = song_.getCumulativeNBeats(position_.asMilliseconds());


        for(int i = 0; i < players.size(); i++) {
            if(players[i] != nullptr) {
                joueurs_[i].setPosition(players[i]->x, players[i]->y);
            }
        }

        for(auto & totem : totems_) {
            totem.update(elapsed, nullptr, currentBeat_, true);
        }

        for(auto & mech : mechanics_) {
            mech->update(elapsed, currentBeat_, manager_);

            if(!GOD_MODE && mech->isFailed()) {
                std::cout << mech->toString() << std::endl;
                Target t = Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW);
                std::cout << manager_.getPosition(t).x << " " << manager_.getPosition(t).y << std::endl;

                failed = true;
            }
        }
    }
}

std::pair<float, float> Lobby::getCheckpoint() {
    return song_.getCurrentCheckpoint(currentBeat_);
}

void Lobby::resetTimer()
{
    position_ = sf::seconds(0);
    currentBeat_ = 0;
}

void Lobby::load(const std::string &filename) {
    song_.load(filename,
               nullptr,
               mechanics_, nullptr);
}
