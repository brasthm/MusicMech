//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_RINGSHAPE_H
#define MUSICMECH_CLIENT_RINGSHAPE_H

#include <SFML/Graphics.hpp>
#include "../main.h"


class RingShape {
private:
    const int NOTE_NB_POINTS = 100;
    float proportion_;
    float thickness_;
    float distance_;
    sf::Vector2f center_;
    sf::Color color_;

    float angle1_, angle2_;

    std::vector<sf::ConvexShape> triangles_;

    void update();

public :
    RingShape();
    RingShape(sf::Vector2f center, float distance, float thickness, float proportion);
    RingShape(sf::Vector2f center, float distance, float thickness, float proportion, sf::Uint32 color);
    void init(sf::Vector2f center, float distance, float thickness, float proportion, sf::Uint32 color);
    void setDistance(float distance);
    void addDistance(float delta);
    void setThickness(float thick);
    void setAlpha(float alpha);
    void setProportion(float proportion);
    void setCenter(sf::Vector2f center);
    void draw(sf::RenderTarget &window);
    void setFillColor(sf::Uint32 fillColor);
};

class RingShapeOutline {
    float outlineThickness_, proportion_, distance_;

    RingShape borderUp_, borderDown_, center_;

public:
    RingShapeOutline(sf::Vector2f center, float distance, float thickness, float proportion, float outline);
    void setDistance(float distance);
    void addDistance(float delta);
    void setThickness(float thick);
    void setAlpha(float alpha);
    void setProportion(float proportion);
    void setCenter(sf::Vector2f center);
    void draw(sf::RenderTarget& window);
    void setFillColor(sf::Uint32 fillColor);
    void setOutlineColor(sf::Uint32 outlineColor);
};


#endif //MUSICMECH_CLIENT_RINGSHAPE_H
