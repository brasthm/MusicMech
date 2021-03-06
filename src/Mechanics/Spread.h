//
// Created by cyril on 30/05/2022.
//

#ifndef MUSICMECH_CLIENT_SPREAD_H
#define MUSICMECH_CLIENT_SPREAD_H

#include "Mechanic.h"
#include "../Graphics/PlayerIndicator.h"
#include "../Graphics/RingShape.h"
#include "../Graphics/ShiftColor.h"


class Spread : public Mechanic {
    sf::CircleShape base_;
    PlayerIndicator playerIndicator_;
    RingShape approachCircle_;
    float radius_, newRadius_;
    int nbShare_, nbIn_;
    bool isShare_;
    ShiftColor backColor_;
    Target target_;
    sf::Vector2f position_;

    void updatePosition(EntityManager &entityManager);
    void setColor();


public:
    Spread(float beat, float radius, int nbShare, float active, const Target &target);
    void onDraw(const sf::Time &elapsed, sf::RenderWindow &window) override;
    void onCheck(const sf::Time &elapsed, float currentBeat, float cuurentPart, EntityManager &entities) override;
    void onApproach(const sf::Time &elapsed, float currentBeat, float cuurentPart, EntityManager &entities) override;
    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) override;
    void onFade(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) override;
    void onInit(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) override;
    void reset(float beat) override;
    std::string toString() override;
};


#endif //MUSICMECH_CLIENT_SPREAD_H
