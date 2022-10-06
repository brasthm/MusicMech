#ifndef MUSICMECH_CLIENT_NOPEZONE_H
#define MUSICMECH_CLIENT_NOPEZONE_H

#include <SFML/Graphics.hpp>
#include "../main.h"
#include "Mechanic.h"
#include "../Graphics/PlayerIndicator.h"

class NopeZone : public Mechanic {
private:
    sf::RectangleShape base_;
    sf::FloatRect rect_;
    PlayerIndicator playerIndicator_;
    float width_, height_;
    int nbShare_, nbIn_;
    bool isShare_;
    
    ShiftColor backColor_;
    Target target_;
    sf::Vector2f position_, shift_;
    float rotation_;
    sf::Time timer_, vibrate_;

    void updatePosition(EntityManager& entityManager);
    void setColor();


public:
    NopeZone(float beat, float width, float height, int nbShare, float active, const Target& target);
    void onDraw(const sf::Time& elapsed, sf::RenderTarget& window) override;
    void onCheck(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities) override;
    void onApproach(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities) override;
    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void onInit(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void reset(float beat) override;
    std::string toString() override;

    Mechanic* clone() override;

};


#endif