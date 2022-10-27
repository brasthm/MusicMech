#ifndef MUSICMECH_CLIENT_TETHER_TEXT_H
#define MUSICMECH_CLIENT_TETHER_TEXT_H

#include "Mechanic.h"
#include "../Graphics/PlayerIndicator.h"
#include "../Graphics/RingShape.h"
#include "../Graphics/ShiftColor.h"
#include "../System/Debuff.h"


class TextIndicator : public Mechanic {
    Target target_;
    sf::Vector2f pos_;
    sf::RectangleShape tether_;
    sf::Text displayText_;
    ShiftColor color_;
    sf::Uint32 colorId_;
    std::string text_;

    void updatePosition(EntityManager& entityManager);


public:
    TextIndicator(float beat, const Target& t1, float duration, std::string text,sf::Uint32 color = 0x42B3F0FF);
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