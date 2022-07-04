//
// Created by cyril on 30/06/2022.
//

#ifndef MUSICMECH_CLIENT_ENTITYMANAGER_H
#define MUSICMECH_CLIENT_ENTITYMANAGER_H


#include <SFML/Graphics.hpp>
#include "Entity.h"

enum TargetType {
    TARGET_POS, TARGET_ENTITY,
    TARGET_RANDOM, TARGET_RANDOM8, TARGET_RANDOM4, TARGET_RANDOM3, TARGET_RANDOM2, TARGET_RANDOM_END,
    TARGET_CLOSEST, TARGET_FURTHEST
};

enum TargetTiming {
    TARGET_ONINIT, TARGET_ONBEAT, TARGET_FOLLOW
};

enum TargetTeam {
    TARGET_PLAYERS, TARGET_TOTEMS
};

class Target {
public:
    TargetType type = TARGET_POS;
    sf::Vector2f pos = {0,0};
    int id = 0;
    int save = -1;
    TargetTiming timing = TARGET_ONINIT;
    TargetTeam team = TARGET_PLAYERS;
    Target *target = nullptr;

    Target(const Target &t);
    Target(TargetType, sf::Vector2f);
    Target(TargetType, TargetTeam, int, TargetTiming = TARGET_ONINIT);
    Target(TargetType, TargetTeam, TargetTiming tt = TARGET_ONINIT);
    Target(TargetType, TargetTeam, int, Target*, TargetTiming);

    ~Target();
};


class EntityManager {
private:
    std::vector<Entity*> players_;
    std::vector<Entity*> totems_;

    std::vector<int> perm_;
    int current_ = 0;

    int getRandomSequence(int n);
    int getBySorted(const Target&target, bool descending=false);
    Entity *getEntity(Target &target);

public:
    EntityManager() = default;
    void addPlayer(Entity* player);
    void addTotem(Entity* totem);
    void clear();
    void clearPlayers();
    void clearTotems();
    sf::Vector2f getPosition(Target &target);
    void setActive(Target &target, bool val);
    void setTargetPosition(Target &entity, Target &target, float speed, bool isInstant);
    int getSizePlayers();
    int getSizeTotems();
    bool getActive(Target &target);
    void applyDebuff(Target &target, DebuffType type, float end);

};


#endif //MUSICMECH_CLIENT_ENTITYMANAGER_H
