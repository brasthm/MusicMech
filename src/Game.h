//
// Created by cyril on 16/05/2022.
//

#ifndef MUSICMECH_CLIENT_GAME_H
#define MUSICMECH_CLIENT_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Client.h"
#include "Joueur.h"

class Game {
private:
    sf::RenderWindow &window_;
    Client *client_;
    bool online_;
    std::vector<Joueur> joueurs_;
public:
    explicit Game(sf::RenderWindow &window);
    Game(sf::RenderWindow &window, Client *client);
    void run();

};


#endif //MUSICMECH_CLIENT_GAME_H
