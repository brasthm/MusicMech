//
// Created by cyril on 16/05/2022.
//

#ifndef MUSICMECH_CLIENT_GAME_H
#define MUSICMECH_CLIENT_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Network/Client.h"
#include "Entity/EntityManager.h"
#include "Entity/Joueur.h"
#include "Entity/Totem.h"
#include "Mechanics/Mechanic.h"
#include "System/Song.h"
#include "System/Arena.h"

class Game {
private:
    sf::Music music_;
    bool online_;
    EntityManager em_;
    std::vector<Joueur> joueurs_;
    std::vector<Totem> totems_;
    std::vector<Mechanic*> mechanicList_;
    Song song_;
    Arena arena_;
public:
    explicit Game();
    ~Game();
    void run(sf::RenderWindow &window, Client* client, bool creator);
    void load();
    void load(const std::string &path);
    void save(const std::string &filename);
    void reset(float beat);
    void clearPlayer();
    void addPlayer(sf::Uint32 color);
};


#endif //MUSICMECH_CLIENT_GAME_H
