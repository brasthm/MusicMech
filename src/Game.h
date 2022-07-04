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

class Game {
private:
    Client *client_;
    bool online_;
    EntityManager em_;
    std::vector<Joueur> joueurs_;
    std::vector<Totem> totems_;
    std::vector<Mechanic*> mechanicList_;
    Song song_;
public:
    explicit Game();
    ~Game();
    Game(Client *client);
    void run(sf::RenderWindow &window, const std::string& roomID);
    void load();
    static bool compareMech(Mechanic *m1, Mechanic *m2);

};


#endif //MUSICMECH_CLIENT_GAME_H
