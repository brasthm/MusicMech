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
    std::vector<int> debuffsNumbers_;
    Song *song_;
    Arena arena_;
    float beat_;
    
public:
    RoomStatus(Song *song, std::vector<Mechanic*> *mechanicList);
    ~RoomStatus();
    int run(sf::RenderWindow& window, Client* client);

    void addJoueur(int i, std::string &name, sf::Uint32 color, bool active, float x, float y);
    void addTotem(int i, sf::Uint32 color, bool active, float x, float y);
    void addFailed(int i);
    void addArenaRect(float rl, float rt, float rw, float rh);
    void setBeat(float beat);
    void setArenaParameters(float zoom, float rotation, float left, float top, float width, float height);
    void setMechPosition(int i, std::vector<sf::Vector2f>& positions);
    void setDebuffs(int i, DebuffType type, float end);

    EntityManager& getEntityManager();
};


#endif //MUSICMECH_CLIENT_GAME_H
