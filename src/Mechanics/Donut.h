#ifndef MUSICMECH_CLIENT_DONUT_H
#define MUSICMECH_CLIENT_DONUT_H

#include "Mechanic.h"
#include "../Graphics/PlayerIndicator.h"
#include "../Graphics/RingShape.h"
#include "../Graphics/ShiftColor.h"


class Donut : public Mechanic {
    PlayerIndicator playerIndicator_;
    RingShapeOutline base_;
    RingShape approachCircle_;
    float distanceMin_, distanceMax_;
    int nbShare_, nbIn_;
    bool isShare_;
    ShiftColor backColor_;
    Target target_;
    sf::Vector2f position_;
    sf::Color outlineColor_;

    DebuffType debuffToApply_;
    float debuffTimer_;

    sf::Time highlightTimer_;
    bool highlight_;

    void updatePosition(EntityManager& entityManager);
    void setColor();


public:
    Donut(float beat, float distanceMin, float distanceMax, int nbShare, float active, const Target& target, DebuffType debuffToApply = DEBUFF_NONE, float debuffTimer = 0);
    void onDraw(const sf::Time& elapsed, sf::RenderTarget& window) override;
    void onCheck(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities) override;
    void onApproach(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities) override;
    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void onInit(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void reset(float beat) override;
    void getTargetPos(std::vector<sf::Vector2f>& pos) override;
    void setTargetPos(std::vector<sf::Vector2f>& pos) override;

    std::string toString() override;
    Mechanic* clone() override;
};

#endif