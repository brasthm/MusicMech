#ifndef MUSICMECH_CLIENT_DISPLAYIMAGE_H
#define MUSICMECH_CLIENT_DISPLAYIMAGE_H

#include <SFML/Graphics.hpp>
#include "../main.h"
#include "Mechanic.h"


class DisplayImage : public Mechanic {
private:
    sf::Sprite base_;
    Target position_;
    sf::Vector2f pos_, shift_;
    std::string path_;
    float rotation_;

    void updatePosition(EntityManager& entityManager);

public:
    DisplayImage(float beat, std::string path, float active, const Target& pos);
    void onDraw(const sf::Time& elapsed, sf::RenderTarget& window) override;
    void onApproach(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities) override;
    void onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void onInit(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    void reset(float beat) override;
    std::string toString() override;
};


#endif