#ifndef MUSICMECH_CLIENT_CONE_H
#define MUSICMECH_CLIENT_CONE_H

#include <SFML/Graphics.hpp>
#include "../main.h"
#include "../Graphics/PlayerIndicator.h"
#include "../Graphics/RingShape.h"
#include "Mechanic.h"


class Cone : public Mechanic {
	private:
    sf::ConvexShape base_;
    PlayerIndicator playerIndicator_;
    RingShape approachCircle_;
    float width_, distance_;
    int nbShare_, nbIn_;
    bool isShare_;
    ShiftColor backColor_;
    Target center_, anchor_;
    sf::Time highlightTimer_;
    bool highlight_;
    sf::Vector2f anchorPos_;
    sf::Vector2f centerPos_;

    void updatePosition(EntityManager& entityManager);
    void setColor();


public:
    Cone(float beat, float width, float distance, int nbShare, float active, const Target& center, const Target& anchor);
    void onDraw(const sf::Time& elapsed, sf::RenderTarget& window) override;
    void onCheck(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities) override;
    void onApproach(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities) override;
    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void onInit(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void reset(float beat) override;
    std::string toString() override;
    void getTargetPos(std::vector<sf::Vector2f>& pos) override;
    void setTargetPos(std::vector<sf::Vector2f>& pos) override;
    Mechanic* clone() override;
};


#endif