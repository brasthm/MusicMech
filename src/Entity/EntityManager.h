//
// Created by cyril on 30/06/2022.
//

#ifndef MUSICMECH_CLIENT_ENTITYMANAGER_H
#define MUSICMECH_CLIENT_ENTITYMANAGER_H


#include <SFML/Graphics.hpp>
#include "Entity.h"

#include "../System/Arena.h"

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

    Target();
    Target(const Target &t);
    Target(TargetType, sf::Vector2f);
    Target(TargetType, TargetTeam, int, TargetTiming = TARGET_ONINIT);
    Target(TargetType, TargetTeam, TargetTiming tt = TARGET_ONINIT);
    Target(TargetType, TargetTeam, int, Target*, TargetTiming);


    std::string to_string() const;
    int parse(int offset, const std::vector<std::string> &words);

    void reset();

    ~Target();
};


class EntityManager {
private:
    std::vector<Entity*> players_;
    std::vector<Entity*> totems_;

    Arena* arena_ = nullptr;

    std::vector<int> perm_;
    int current_ = 0;

    int getRandomSequence(int n);
    int getBySorted(const Target&target, bool descending=false);

    bool cleared_ = false;

    Entity *getEntity(Target &target);

public:
    EntityManager() = default;
    void addPlayer(Entity* player);
    void addTotem(Entity* totem);
    void addArena(Arena* arena);
    void clear();
    void clearPlayers();
    void clearTotems();
    void clearArena();
    void resetArena();
    sf::Vector2f getPosition(Target &target);
    Arena* getArena();
    void setActive(Target &target, bool val, sf::Uint32 color);
    void setTargetPosition(Target &entity, Target &target, float speed, bool isInstant);
    int getSizePlayers();
    int getSizeTotems();
    bool getActive(Target &target);
    void applyDebuff(Target &target, DebuffType type, float end);
    void zoomArena(float val, float speed);
    void rotateArena(float val, float speed);
    void moveArena(float x, float y, float speed);
    void snapArena(float x, float y);
    void addArenaPortion(float x, float y, float w, float h);
    void removeArenaPortion(int index);
   
    void startEndAnim();
    bool getCleared();

};


#endif //MUSICMECH_CLIENT_ENTITYMANAGER_H
