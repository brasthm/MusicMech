//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_RINGSHAPE_H
#define MUSICMECH_CLIENT_RINGSHAPE_H

#include <SFML/Graphics.hpp>
#include "main.h"



class RingShape {
private:
    const int NOTE_NB_POINTS = 16;
    size_t proportion_;
    float thickness_;
    float distance_;
    sf::Vector2f center_;

    float angle1_, angle2_;

    std::vector<sf::ConvexShape> triangles_;

    void update();

public :
    RingShape();
    RingShape(sf::Vector2f center, float distance, float thickness, float proportion);
    void init(sf::Vector2f center, float distance, float thickness, float proportion);
    void setDistance(float distance);
    void addDistance(float delta);
    void setThickness(float thick);
    void draw(sf::RenderWindow &window);
};


#endif //MUSICMECH_CLIENT_RINGSHAPE_H
