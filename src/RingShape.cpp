//
// Created by cyril on 21/05/2022.
//

#include "RingShape.h"

#include <cmath>
#include <iostream>

void RingShape::update()
{
    triangles_.clear();

    float delta = 2.f*(angle2_ - angle1_) / (float)NOTE_NB_POINTS;

    for (int i = 0; i < NOTE_NB_POINTS / 2; i++)
    {

        // Triangle 1
        triangles_.emplace_back(3);

        triangles_.back().setPoint(0, center_ + sf::Vector2f(distance_*cos(angle1_ + delta*i), distance_*sin(angle1_ + delta*i)));
        triangles_.back().setPoint(1, center_ + sf::Vector2f(distance_*cos(angle1_ + delta*(i + 1)), distance_*sin(angle1_ + delta*(i + 1))));
        triangles_.back().setPoint(2, center_ + sf::Vector2f((thickness_ + distance_)*cos(angle1_ + delta*i), (thickness_ + distance_)*sin(angle1_ + delta*i)));
        triangles_.back().setFillColor(color_);

        // Triangle 2
        triangles_.emplace_back(3);

        triangles_.back().setPoint(0, center_ + sf::Vector2f(distance_*cos(angle1_ + delta*(i + 1)), distance_*sin(angle1_ + delta*(i + 1))));
        triangles_.back().setPoint(1, center_ + sf::Vector2f((thickness_ + distance_)*cos(angle1_ + delta*(i)), (thickness_ + distance_)*sin(angle1_ + delta*(i))));
        triangles_.back().setPoint(2, center_ + sf::Vector2f((thickness_ + distance_)*cos(angle1_ + delta*(i + 1)), (thickness_ + distance_)*sin(angle1_ + delta*(i + 1))));
        triangles_.back().setFillColor(color_);

    }
}

RingShape::RingShape()
{
}

RingShape::RingShape(sf::Vector2f center, float distance, float thickness, float proportion)
{
    init(center, distance, thickness, proportion);
}

void RingShape::init(sf::Vector2f center, float distance, float thickness, float proportion)
{
    color_ = sf::Color(0x79CE1BFF);
    center_ = center;
    distance_ = distance;
    thickness_ = thickness;
    proportion_ = proportion;
    angle1_ = -PI/2;
    angle2_ = angle1_ + 2 * PI * proportion_;

    update();
}

void RingShape::setDistance(float distance)
{
    distance_ = distance;
    update();
}

void RingShape::addDistance(float delta)
{
    distance_ += delta;
    update();
}

void RingShape::setThickness(float thick)
{
    thickness_ = thick;
}

void RingShape::draw(sf::RenderWindow & window)
{
    for (int i = 0; i < triangles_.size(); i++)
        window.draw(triangles_[i]);
}

void RingShape::setProportion(float proportion) {
    proportion_ = proportion;
    angle2_ = angle1_ + 2.f * PI * proportion_;

    update();
}

void RingShape::setAlpha(float alpha) {
    color_.a = alpha;
    update();
}
