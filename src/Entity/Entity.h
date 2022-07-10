//
// Created by cyril on 25/06/2022.
//

#ifndef MUSICMECH_CLIENT_ENTITY_H
#define MUSICMECH_CLIENT_ENTITY_H

#include <SFML/Graphics.hpp>
#include "../System/Debuff.h"


class Entity {
protected:
    sf::CircleShape shape_;
    sf::Vector2f pos_, targetPos_;
    sf::Vector2f serv_pos_;
    float speed_=0, radius_=0, baseSpeed_=0;
    bool active_=false;
    Debuff debuff_;

public:
    Entity() = default;
    inline int getPosX() const {return pos_.x;};
    inline int getPosY() const {return pos_.y;};
    inline sf::Vector2f getPos() const {return pos_;};
    inline sf::Vector2f getServerPos() const {return serv_pos_;};

    inline void setActive(bool val) {active_ = val;};
    inline bool getActive() {return  active_; };

    void setTarget(const sf::Vector2f &, float speed, bool isInstant);
    void setPosition(float x, float y);

    virtual void update(sf::Time elapsed, float beat, bool hasFocus) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    void applyDebuff(DebuffType type, float end);
};


#endif //MUSICMECH_CLIENT_ENTITY_H
