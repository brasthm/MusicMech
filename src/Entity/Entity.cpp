//
// Created by cyril on 25/06/2022.
//

#include "Entity.h"


void Entity::setTarget(const sf::Vector2f &pos, float speed, bool isInstant) {
    if(speed != -1) speed_ = speed;
    targetPos_ = pos;
    if(isInstant) pos_ = pos;
}

void Entity::applyDebuff(DebuffType type, float end) {
    debuff_.apply(type, end);
}

void Entity::setColor(sf::Uint32 color)
{
    color_ = color;
}

sf::Uint32 Entity::getColor()
{
    return color_;
}

void Entity::setPosition(float x, float y) {
    pos_.x = x;
    pos_.y = y;
}

void Entity::setServerPosition(float x, float y)
{
    serv_pos_.x = x;
    serv_pos_.y = y;
}
