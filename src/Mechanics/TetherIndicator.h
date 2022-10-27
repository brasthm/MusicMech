#ifndef MUSICMECH_CLIENT_TETHER_INDICATOR_H
#define MUSICMECH_CLIENT_TETHER_INDICATOR_H

#include "Mechanic.h"
#include "../Graphics/PlayerIndicator.h"
#include "../Graphics/RingShape.h"
#include "../Graphics/ShiftColor.h"
#include "../System/Debuff.h"


class TetherIndicator : public Mechanic {
    Target anchor1_, anchor2_;
    sf::Vector2f pos1_, pos2_;
    sf::RectangleShape tether_;
    ShiftColor color_;
    sf::Uint32 colorId_;

public:
    TetherIndicator(float beat, const Target& t1, const Target& t2, float duration, sf::Uint32 color = 0xF8C08Bff);
    void onDraw(const sf::Time& elapsed, sf::RenderTarget& window) override;
    void onApproach(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& em) override;
    void onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& em) override;
    void reset(float beat) override;
    void getTargetPos(std::vector<sf::Vector2f>& pos) override;
    void setTargetPos(std::vector<sf::Vector2f>& pos) override;

    std::string toString() override;
    Mechanic* clone() override;


};

#endif