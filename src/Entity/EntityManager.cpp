//
// Created by cyril on 30/06/2022.
//

#include "EntityManager.h"
#include "../System/Random.h"
#include "../System/Utils.h"

#include <algorithm>

Target::Target(TargetType t, sf::Vector2f p) {
    type = t;
    pos = p;
    id = -1;
}

Target::Target(TargetType ty, TargetTeam t, int i, TargetTiming tt) {
    type = ty;
    team = t;
    timing = tt;
    id = i;
}

Target::Target(TargetType ty, TargetTeam t, TargetTiming tt) {
    type = ty;
    team = t;
    timing = tt;
    id = -1;
}

Target::Target(TargetType ty, TargetTeam t, int i, Target *targ, TargetTiming tt) {
    type = ty;
    team = t;
    id = i;
    target = targ;
    timing = tt;
}

Target::~Target() {
    delete target;
}

Target::Target(const Target &t) {
    timing = t.timing;
    target = t.target;
    type = t.type;
    team = t.team;
    pos = t.pos;
    id = t.id;
    target = t.target != nullptr ? new Target(*t.target) : nullptr;
}

std::string Target::to_string() const {
    std::string res;
    res = std::to_string(timing) + "," + std::to_string(type) + "," +std::to_string(team) +
            "," + std::to_string(pos.x) + "," + std::to_string(pos.y) + "," +  std::to_string(id) + ",";

    if(target == nullptr)
        res += "NULL";
    else
        res += "TARGET," + target->to_string();
    return res;
}

Target::Target() = default;

int Target::parse(int offset, const std::vector<std::string> &words) {
    timing = static_cast<TargetTiming>(std::stoi(words[offset]));
    type = static_cast<TargetType>(std::stoi(words[offset+1]));
    team = static_cast<TargetTeam>(std::stoi(words[offset+2]));
    pos.x = std::stof(words[offset+3]);
    pos.y = std::stof(words[offset+4]);
    id = std::stoi(words[offset+5]);

    if(words[offset+6] == "NULL") {
        target = nullptr;
    }
    else {
        target = new Target();
        return target->parse(offset+7, words);
    }

    return offset + 7;
}


void EntityManager::addPlayer(Entity *player) {
    players_.push_back(player);
}

void EntityManager::addTotem(Entity *totem) {
    totems_.push_back(totem);
}

void EntityManager::addArena(Arena* arena)
{
    arena_ = arena;
}

sf::Vector2f EntityManager::getPosition(Target &target) {
    Entity *en = getEntity(target);
    return en == nullptr ? target.pos:en->getPos();
}

Arena* EntityManager::getArena()
{
    return arena_;
}

int EntityManager::getRandomSequence(int n) {
    if(current_ == 0) {
        perm_.clear();
        for(int i = 0; i < n; i++)
            perm_.push_back(i);
        Random::shuffle(perm_);
    }
    int val = perm_[current_];
    current_ = (current_+1) % n;
    return val;
}

Entity *EntityManager::getEntity(Target &target) {
    std::vector<Entity*> active;

    switch(target.type) {
        case TARGET_POS:
            return nullptr;
        case TARGET_ENTITY:
            return target.team == TARGET_TOTEMS ? totems_[target.id] :
                   players_[target.id];
        case TARGET_RANDOM:

            if(target.team == TARGET_TOTEMS) {
                for(int  i = 0; i < totems_.size(); i++)
                    if(totems_[i]->getActive())
                        active.push_back(totems_[i]);
            }

            if(target.team == TARGET_PLAYERS) {
                for(int  i = 0; i < players_.size(); i++)
                    if(players_[i]->getActive())
                        active.push_back(players_[i]);
            }
            if(target.save == -1) {
                target.save = Random::randint(0, active.size());
            }

            return active[target.save];
        case TARGET_RANDOM2:
            if(target.save == -1) {
                target.save = getRandomSequence(2);
            }
            return target.team == TARGET_TOTEMS ? totems_[target.save]:players_[target.save];
        case TARGET_RANDOM3:
            if(target.save == -1) {
                target.save = getRandomSequence(3);
            }
            return target.team == TARGET_TOTEMS ? totems_[target.save]:players_[target.save];
        case TARGET_RANDOM4:
            if(target.save == -1) {
                target.save = getRandomSequence(4);
            }
            return target.team == TARGET_TOTEMS ? totems_[target.save]:players_[target.save];
        case TARGET_RANDOM8:
            if(target.save == -1) {
                target.save = getRandomSequence(8);
            }
            return target.team == TARGET_TOTEMS ? totems_[target.save]:players_[target.save];
        case TARGET_RANDOM_END:
            if(target.save == -1) {
                target.save = getRandomSequence(1000);
                current_ = 0;
            }
            return target.team == TARGET_TOTEMS ? totems_[target.save]:players_[target.save];
        case TARGET_CLOSEST:
            if(target.timing != TARGET_FOLLOW) {
                if(target.save == -1) {
                    target.save = getBySorted(target);
                }
                return target.team == TARGET_TOTEMS ? totems_[target.save]:players_[target.save];
            }
            return target.team == TARGET_TOTEMS ? totems_[getBySorted(target)]:players_[getBySorted(target)];
        case TARGET_FURTHEST:
            if(target.timing != TARGET_FOLLOW) {
                if(target.save == -1) {
                    target.save = getBySorted(target, true);
                }
                return target.team == TARGET_TOTEMS ? totems_[target.save]:players_[target.save];
            }
            return target.team == TARGET_TOTEMS ? totems_[getBySorted(target, true)]:players_[getBySorted(target, true)];
        default:
            return nullptr;
    }
}

int EntityManager::getBySorted(const Target &target, bool descending) {

    std::vector<std::pair<int, float>> distances;

    sf::Vector2f t = getPosition(*target.target);

    if(target.team == TARGET_TOTEMS) {
        for(int  i = 0; i < totems_.size(); i++)
            if(totems_[i]->getActive())
                distances.emplace_back(i, Utils::distance(t, totems_[i]->getPos()));
    }

    if(target.team == TARGET_PLAYERS) {
        for(int  i = 0; i < players_.size(); i++)
            if(players_[i]->getActive())
                distances.emplace_back(i, Utils::distance(t, players_[i]->getPos()));
    }

    if(descending) {
        std::sort(distances.begin(), distances.end(),
                  [] (std::pair<int, float> a, std::pair<int, float> b) {
                      return a.second > b.second;
                  });
    }
    else {
        std::sort(distances.begin(), distances.end(),
                  [] (std::pair<int, float> a, std::pair<int, float> b) {
                      return a.second < b.second;
                  });
    }



    return distances[target.id].first;
}

void EntityManager::setActive(Target &target, bool val, sf::Uint32 color) {
    getEntity(target)->setActive(val);
    getEntity(target)->setColor(color);
}

void EntityManager::setTargetPosition(Target &entity, Target &target, float speed, bool isInstant) {
    getEntity(entity)->setTarget(getPosition(target), speed, isInstant);
}

bool EntityManager::getActive(Target &target) {
    return getEntity(target)->getActive();
}

int EntityManager::getSizePlayers() {
    return players_.size();
}

int EntityManager::getSizeTotems() {
    return totems_.size();
}

void EntityManager::clearPlayers() {
    players_.clear();
}

void EntityManager::clearTotems() {
    totems_.clear();
}

void EntityManager::clearArena()
{
    if(arena_ != nullptr)
        arena_ = nullptr;
}

void EntityManager::resetArena()
{
    arena_->clear();
}

void EntityManager::clear() {
    clearTotems();
    clearPlayers();
    clearArena();
    current_ = 0;
    cleared_ = false;
}

void EntityManager::applyDebuff(Target &target, DebuffType type, float end) {
    getEntity(target)->applyDebuff(type, end);
}

void EntityManager::zoomArena(float val, float speed)
{
    if (arena_ != nullptr)
        arena_->zoom(val, speed);
}

void EntityManager::rotateArena(float val, float speed)
{
    if (arena_ != nullptr)
        arena_->rotate(val, speed);
}

void EntityManager::moveArena(float x, float y, float speed)
{
    if (arena_ != nullptr)
        arena_->move(x, y, speed);
}

void EntityManager::snapArena(float x, float y)
{
    if (arena_ != nullptr)
        arena_->snap(x, y);
}

void EntityManager::addArenaPortion(float x, float y, float w, float h)
{
    if (arena_ != nullptr)
        arena_->addRect(x, y, w, h);
}

void EntityManager::removeArenaPortion(int index)
{
    if (arena_ != nullptr)
        arena_->erase(index);
}

void EntityManager::startEndAnim()
{
    cleared_ = true;
}

bool EntityManager::getCleared()
{
    return cleared_;
}

