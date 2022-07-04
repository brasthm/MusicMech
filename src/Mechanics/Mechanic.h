//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_MECHANIC_H
#define MUSICMECH_CLIENT_MECHANIC_H

#include <SFML/Graphics.hpp>

#include "../Entity/EntityManager.h"


class Mechanic {
protected:
    float beat_;
    std::string sound_;
    bool played_, checked_;
    bool passed_;
    bool draw_;
    bool init_;
    float active_;
    int drawPriority_;

    void setSoundName(const std::string& name);
    void playSound();
public:
    Mechanic();
    ~Mechanic() = default;
    void update(const sf::Time &elapsed, float currentBeat, EntityManager &entities);
    void draw(const sf::Time &elapsed, sf::RenderWindow &window);

    int getDrawPriority() const;
    bool operator< (const Mechanic& mech) const;
    float getBeat() const;


    virtual std::string toString() { return ""; };
    virtual inline void onInit(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {};
    virtual inline void onDraw(const sf::Time &elapsed, sf::RenderWindow &window) {};
    virtual inline void onCheck(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {};
    virtual inline void onApproach(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {};
    virtual inline void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {};
    virtual inline void onFailed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {};
    virtual inline void onFade(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {};


};




#endif //MUSICMECH_CLIENT_MECHANIC_H
