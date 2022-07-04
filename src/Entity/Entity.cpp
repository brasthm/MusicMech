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
