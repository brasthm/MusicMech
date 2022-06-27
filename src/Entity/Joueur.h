//
// Created by cyril on 17/05/2022.
//

#ifndef MUSICMECH_CLIENT_JOUEUR_H
#define MUSICMECH_CLIENT_JOUEUR_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Entity.h"

class Joueur : public Entity {
private:
    sf::Vector2f serv_pos_;
    bool controlledByPlayer_, connected_;
    std::string name_;
public:
    Joueur();
    void update(sf::Time elapsed, bool hasFocus) override;
    void draw(sf::RenderWindow &window) override;
    bool getConnected() const {return connected_;};
    void setConnected(bool b) {connected_=b;};
    void setControlledByPlayer(bool b) {controlledByPlayer_=b;};
    void setDataFromServer(sf::Packet &packet);
};


#endif //MUSICMECH_CLIENT_JOUEUR_H
