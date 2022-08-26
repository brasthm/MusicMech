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
    bool controlledByPlayer_;
    std::string name_;
public:
    Joueur();
    void update(sf::Time elapsed, Arena* arena, float beat, bool hasFocus) override;
    void draw(sf::RenderTarget &window) override;
    void setControlledByPlayer(bool b) {controlledByPlayer_=b;};
    void setDataFromServer(sf::Packet &packet);
    void reset();
};


#endif //MUSICMECH_CLIENT_JOUEUR_H
