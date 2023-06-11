//
// Created by cyril on 30/05/2022.
//

#ifndef MUSICMECH_CLIENT_SPREAD_H
#define MUSICMECH_CLIENT_SPREAD_H

#include "Mechanic.h"
#include "../Graphics/PlayerIndicator.h"
#include "../Graphics/RingShape.h"
#include "../Graphics/ShiftColor.h"
#include "../System/Debuff.h"


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
    sf::Time highlightTimer_;
    bool highlight_;
    DebuffType debuffToApply_;
    float debuffTimer_;
    std::string colorScheme_;
    std::vector<int> allIns_;

    void updatePosition(EntityManager &entityManager);
    void setColor();


public:
    Spread(float beat, float radius, int nbShare, float active, const Target &target, DebuffType debuffToApply = DEBUFF_NONE, float debuffTimer = 0, const std::string &colorScheme = "default");
    void onDraw(const sf::Time &elapsed, sf::RenderTarget &window) override;
    void onCheck(const sf::Time &elapsed, float currentBeat, float cuurentPart, EntityManager &entities) override;
    void onApproach(const sf::Time &elapsed, float currentBeat, float cuurentPart, EntityManager &entities) override;
    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) override;
    void onFailed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void onFade(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) override;
    void onInit(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) override;
    void reset(float beat) override;
    void getTargetPos(std::vector<sf::Vector2f>& pos) override;
    void setTargetPos(std::vector<sf::Vector2f>& pos) override;

    std::string toString() override;
    Mechanic* clone() override;
};


#endif //MUSICMECH_CLIENT_SPREAD_H
