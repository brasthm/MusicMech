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
    sf::RectangleShape namePlate_;
    sf::Text nameText_;
    sf::Clock plateTimer_;
    sf::Time plateLimit_;

    bool drawPlate_;
    float plateOpacity_;
    

    
public:
    Joueur();
    bool update(sf::Time elapsed, Arena* arena, float beat, bool hasFocus);
    void draw(sf::RenderTarget &window, bool serverPos);
    void setControlledByPlayer(bool b) {controlledByPlayer_=b;};
    void setDataFromServer(sf::Packet &packet);
    void reset();
    void setName(std::string name);
    void showPlate(bool permanant = false);
    void hidePlate();
    void computePlate();

    std::string getName();
};


#endif //MUSICMECH_CLIENT_JOUEUR_H
