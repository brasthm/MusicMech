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
    debuffs_.emplace_back();
    debuffs_.back().apply(type, end);
}

void Entity::setColor(sf::Uint32 color)
{
    color_ = color;
}

sf::Uint32 Entity::getColor()
{
    return color_;
}

void Entity::getCurrentDebuffs(std::vector<DebuffType>& debuffs)
{
    debuffs.clear();
    for (int i = 0; i < debuffs_.size(); i++) {
        debuffs.emplace_back(debuffs_[i].type());
    }
}

void Entity::getCurrentDebuffs(std::vector<std::pair<DebuffType, float>>& debuffs) {
    debuffs.clear();
    for (int i = 0; i < debuffs_.size(); i++) {
        if (debuffs_[i].type() != DEBUFF_NONE)
            debuffs.emplace_back(debuffs_[i].type(), debuffs_[i].getEnd());
    }
}

void Entity::getDebuffs(std::vector<DebuffInfo>& debuffsInfo)
{
    debuffsInfo.clear();
    for (int i = 0; i < debuffs_.size(); i++) {
        if (debuffs_[i].getDrawIcon()) {
            DebuffInfo info;
            info.name = debuffs_[i].getName();
            info.desc = debuffs_[i].getDesc();
            info.icon = debuffs_[i].getIcon();
            info.end = debuffs_[i].getEnd();
            debuffsInfo.emplace_back(info);
        }
    }
}

void Entity::changeDebuff(int index, DebuffType type, float end)
{
    debuffs_[index].set(type, end);
}

void Entity::setRadius(float radius)
{
    radius_ = radius;
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

void Entity::setIndex(int ind)
{
    index_ = ind;
}

int Entity::getIndex()
{
    return index_;
}

