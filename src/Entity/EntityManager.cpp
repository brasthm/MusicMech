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


void EntityManager::addPlayer(Entity *player) {
    players_.push_back(player);
}

void EntityManager::addTotem(Entity *totem) {
    totems_.push_back(totem);
}

sf::Vector2f EntityManager::getPosition(Target &target) {
    Entity *en = getEntity(target);
    return en == nullptr ? target.pos:en->getPos();
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

    Entity *t = getEntity(*target.target);

    if(target.team == TARGET_TOTEMS) {
        for(int  i = 0; i < totems_.size(); i++)
            if(totems_[i]->getActive())
                distances.emplace_back(i, Utils::distance(t->getPos(), totems_[i]->getPos()));
    }

    if(target.team == TARGET_PLAYERS) {
        for(int  i = 0; i < players_.size(); i++)
            if(players_[i]->getActive())
                distances.emplace_back(i, Utils::distance(t->getPos(), players_[i]->getPos()));
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

void EntityManager::setActive(Target &target, bool val) {
    getEntity(target)->setActive(val);
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
    players_.clear();
}

void EntityManager::clear() {
    clearTotems();
    clearPlayers();
    current_ = 0;
}

void EntityManager::applyDebuff(Target &target, DebuffType type, float end) {
    getEntity(target)->applyDebuff(type, end);
}

