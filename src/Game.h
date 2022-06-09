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
    Client *client_;
    bool online_;
    std::vector<Joueur> joueurs_;
public:
    explicit Game();
    Game(Client *client);
    void run(sf::RenderWindow &window);

};


#endif //MUSICMECH_CLIENT_GAME_H
