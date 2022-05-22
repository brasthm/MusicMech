//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_TOWER_H
#define MUSICMECH_CLIENT_TOWER_H

#include "Mechanic.h"
#include "RingShape.h"

class Tower : public Mechanic{
private:
    sf::CircleShape base_;
    RingShape approachCircle_;
    sf::Vector2f position_;
    float radius_, newRadius_;
    bool draw_, hitsound_;
public:
    Tower(int beat, sf::Vector2f position, float radius);
    void draw(sf::RenderWindow &window) override;
    void update(int currentBeat, float currentPart, sf::Vector2f pos) override;
    void check(sf::Vector2f pos) override;
};


#endif //MUSICMECH_CLIENT_TOWER_H
