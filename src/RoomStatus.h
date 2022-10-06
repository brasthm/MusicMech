#ifndef MUSICMECH_CLIENT_ROOMSTATUS_H
#define MUSICMECH_CLIENT_ROOMSTATUS_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Network/Client.h"
#include "Entity/EntityManager.h"
#include "Entity/Joueur.h"
#include "Entity/Totem.h"
#include "Mechanics/Mechanic.h"
#include "System/Song.h"
#include "System/Arena.h"

class Client;

class RoomStatus {
private:
    EntityManager em_;
    std::vector<Joueur> joueurs_;
    std::vector<Totem> totems_;
    std::vector<Mechanic*> mechanicList_;
    std::vector<int> failed_;
    Song *song_;
    Arena arena_;
    float beat_;
    
public:
    RoomStatus(Song *song, std::vector<Mechanic*> *mechanicList);
    ~RoomStatus();
    int run(sf::RenderWindow& window, Client* client);
    void clear();

    void setup(RoomStatusData& data);
};


#endif //MUSICMECH_CLIENT_GAME_H
