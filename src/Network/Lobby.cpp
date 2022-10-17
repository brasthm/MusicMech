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

Lobby::Lobby()
{
    status = LobbyStatus::LOBBY_AVAILABLE;
    limit = nbIn = 0;
    for (int i = 0; i < NB_MAX_JOUEURS; i++) {
        players.emplace_back(nullptr);
        joueurs_.emplace_back();
    }
    for (int i = 0; i < NB_MAX_TOTEM; i++) {
        totems_.emplace_back();
    }

    name = "";
    id = "";

    failed = false;
    paused = true;
    currentBeat_ = 0;
}

Lobby::~Lobby()
{
}


void Lobby::startGame() {

    manager_.clear();
    for (int i = 0; i < NB_MAX_JOUEURS; i++) {
        manager_.addPlayer(std::addressof(joueurs_[i]));
    }
    for (int i = 0; i < NB_MAX_TOTEM; i++) {
        manager_.addTotem(std::addressof(totems_[i]));
    }

    manager_.addArena(&arena_);

    failed = false;
    paused = false;
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
        position_ += elapsed;
        currentBeat_ = song_.getCumulativeNBeats(position_.asMilliseconds());

        if (currentSection_ < song_.getCheckpoint(currentBeat_ - TRANSITION_DELAY)) {
            currentSection_ = song_.getCheckpoint(currentBeat_ - TRANSITION_DELAY);
            std::cout << "Lobby " << id << " : Changed section (" << currentSection_ << ")" << std::endl;
        }


        for(int i = 0; i < players.size(); i++) {
            if(players[i] != nullptr) {
                joueurs_[i].setPosition(players[i]->x, players[i]->y);
            }
        }

        for(auto & totem : totems_) {
            totem.update(elapsed, &arena_, currentBeat_);
        }

        arena_.update(elapsed);

        for (int i = 0; i < mechanics_.size(); i++) {
            mechanics_[i]->update(elapsed, currentBeat_, manager_);

            if(!GOD_MODE && mechanics_[i]->isFailed()) {
                std::cout << i << " : " << mechanics_[i]->toString() << std::endl;

                failed = true;
            }
            if (GOD_MODE && mechanics_[i]->isFailed()) {
                //mechanics_[i]->negateFailed();
            }
        }
    }
}

std::pair<float, float> Lobby::getCheckpoint() {
    auto ind = song_.getCheckpoint(currentBeat_ - TRANSITION_DELAY);

    if (ind == -1)
        return std::pair<float, float>(0, 0);

    if (ind < currentSection_) {
        return song_.getIndexCheckpoint(currentSection_);
    }

    return song_.getIndexCheckpoint(ind);
}

void Lobby::resetTimer()
{
    arena_.clear();
    position_ = sf::seconds(0);
    currentBeat_ = 0;
    currentSection_ = -1;
}

float Lobby::getCurrentBeat()
{
    return currentBeat_;
}

float Lobby::getPosition()
{
    return position_.asSeconds();
}

void Lobby::setStatusPacket(sf::Packet &packet)
{

    packet << currentBeat_;

    std::cout << "Current beat : " << currentBeat_ << std::endl;

    std::vector<sf::Int32> failedMechs, drawMech;
    std::vector<std::vector<sf::Vector2f>> drawMechPosition;
    for (int i = 0; i < mechanics_.size(); i++) {
        if (mechanics_[i]->isFailed()) {
            failedMechs.emplace_back(i);
        }
    }

    for (int i = 0; i < mechanics_.size(); i++) {
        if (mechanics_[i]->getDraw()) {
            drawMech.emplace_back(i);
            drawMechPosition.emplace_back();
            mechanics_[i]->getTargetPos(drawMechPosition.back());
        }
    }



    packet << (sf::Int32)failedMechs.size();

    std::cout << "Failed mechs : " << (sf::Int32)failedMechs.size() << std::endl;

    for (int i = 0; i < failedMechs.size(); i++) {
        packet << failedMechs[i];

        std::cout << "      " << failedMechs[i] << " " << std::endl;
    }

    std::cout << "Draw mech position : "  << drawMech.size() << std::endl;
    packet << (sf::Int32)drawMech.size();
    for (int i = 0; i < drawMech.size(); i++) {
        packet << (sf::Int32)drawMech[i] << (sf::Int32)drawMechPosition[i].size();
        for (int j = 0; j < drawMechPosition[i].size(); j++) {
            packet << drawMechPosition[i][j].x << drawMechPosition[i][j].y;

            std::cout << "       " << drawMech[i] << " - (" << drawMechPosition[i][j].x << "; " << drawMechPosition[i][j].y << std::endl;
        }
     }

    packet << sf::Int32(arena_.getNbRects());


    packet << arena_.getZoom() << arena_.getRotation() <<
        arena_.getTop() << arena_.getLeft() << arena_.getWidth() << arena_.getHeight();

    std::cout << "Zoom : " << arena_.getZoom() << std::endl;
    std::cout << "Rotation : " << arena_.getRotation() << std::endl;
    std::cout << "Top : " << arena_.getTop() << std::endl;
    std::cout << "Left : " << arena_.getLeft() << std::endl;
    std::cout << "width : " << arena_.getWidth() << std::endl;
    std::cout << "Height : " << arena_.getHeight() << std::endl;

    std::cout << "Arena : " << sf::Int32(arena_.getNbRects()) << std::endl;

    for (int i = 0; i < arena_.getNbRects(); i++) {
        packet << arena_.getRects(i).top << arena_.getRects(i).left <<
            arena_.getRects(i).width << arena_.getRects(i).height;

        std::cout << "      " << arena_.getRects(i).top << " " << arena_.getRects(i).left << " " <<
            arena_.getRects(i).width << " " << arena_.getRects(i).height << " " << std::endl;
    }

    std::cout << "Totems : " << std::endl;
    for (int i = 0; i < totems_.size(); i++) {
        packet << totems_[i].getColor() << sf::Int32(totems_[i].getActive()) << sf::Int32(totems_[i].getPosX()) << sf::Int32(totems_[i].getPosY());
        
        std::cout << "      " << totems_[i].getColor() << " " << totems_[i].getActive() << " " <<
            (sf::Int32)totems_[i].getPosX() << " " << (sf::Int32)totems_[i].getPosY() << " " << std::endl;
    }

    std::cout << "Joueurs : " << std::endl;
    for (int i = 0; i < joueurs_.size(); i++) {
        packet << sf::String(joueurs_[i].getName()) << joueurs_[i].getColor() << sf::Int32(joueurs_[i].getActive()) << sf::Int32(joueurs_[i].getPosX()) << sf::Int32(joueurs_[i].getPosY());

        std::cout << "      " << sf::String(joueurs_[i].getName()).toAnsiString() << " " << joueurs_[i].getColor() << " " << joueurs_[i].getActive() << " " <<
            joueurs_[i].getPosX() << " " << joueurs_[i].getPosY() << " " << std::endl;
    }
}

void Lobby::setPlayer(int i, std::string name, sf::Uint32 color)
{
    joueurs_[i].setName(name);
    joueurs_[i].setColor(color);
}

void Lobby::load(const std::string &filename) {
    song_.load(filename,
               nullptr,
               mechanics_, &arena_);

    std::cout << "Arena : " << arena_.getNbRects() << std::endl;
    std::cout << "Mechanics number : " << mechanics_.size() << std::endl;

    std::sort(mechanics_.begin(), mechanics_.end(),
        [](Mechanic* m1, Mechanic* m2) {return *m1 < *m2; });
}
