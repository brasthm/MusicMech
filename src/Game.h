//
// Created by cyril on 16/05/2022.
//

#ifndef MUSICMECH_CLIENT_GAME_H
#define MUSICMECH_CLIENT_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Client.h"
#include "Joueur.h"
#include "Mechanic.h"
#include "Song.h"

class Game {
private:
    Client *client_;
    bool online_;
    std::vector<Joueur> joueurs_;
    std::vector<Mechanic*> mechanicList_;
    Song song_;
public:
    explicit Game();
    ~Game();
    Game(Client *client);
    void run(sf::RenderWindow &window, std::string roomID);
    void load();
    static bool compareMech(Mechanic *m1, Mechanic *m2);

};


#endif //MUSICMECH_CLIENT_GAME_H
