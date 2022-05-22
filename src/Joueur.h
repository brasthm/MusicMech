//
// Created by cyril on 17/05/2022.
//

#ifndef MUSICMECH_CLIENT_JOUEUR_H
#define MUSICMECH_CLIENT_JOUEUR_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Joueur {
private:
    sf::CircleShape shape_;
    sf::Vector2f pos_, serv_pos_;
    float speed_;
    bool controlledByPlayer_, connected_;
public:
    Joueur();
    void update(sf::Time elapsed, bool hasFocus);
    void draw(sf::RenderWindow &window);
    bool getConnected() const {return connected_;};
    void setConnected(bool b) {connected_=b;};
    void setControlledByPlayer(bool b) {controlledByPlayer_=b;};
    void setDataFromServer(sf::Packet &packet);
    inline int getPosX() const {return pos_.x;};
    inline int getPosY() const {return pos_.y;};
    inline sf::Vector2f getPos() const {return pos_;};
};


#endif //MUSICMECH_CLIENT_JOUEUR_H
