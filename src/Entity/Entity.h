//
// Created by cyril on 25/06/2022.
//

#ifndef MUSICMECH_CLIENT_ENTITY_H
#define MUSICMECH_CLIENT_ENTITY_H

#include <SFML/Graphics.hpp>


class Entity {
protected:
    sf::CircleShape shape_;
    sf::Vector2f pos_, targetPos_;
    float speed_=0, radius_=0, baseSpeed_=0;

public:
    Entity() = default;
    inline int getPosX() const {return pos_.x;};
    inline int getPosY() const {return pos_.y;};
    inline sf::Vector2f getPos() const {return pos_;};

    void setTarget(const sf::Vector2f &, float speed, bool isInstant);

    virtual void update(sf::Time elapsed, bool hasFocus) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};


#endif //MUSICMECH_CLIENT_ENTITY_H
