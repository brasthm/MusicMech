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
    bool controlledByPlayer_;
    std::string name_;
public:
    Joueur();
    void update(sf::Time elapsed, float beat, bool hasFocus) override;
    void draw(sf::RenderWindow &window) override;
    void setControlledByPlayer(bool b) {controlledByPlayer_=b;};
    void setDataFromServer(sf::Packet &packet);
};


#endif //MUSICMECH_CLIENT_JOUEUR_H
