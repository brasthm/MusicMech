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
    init(center, distance, thickness, proportion, 0xFFFFFFFF);
}

RingShape::RingShape(sf::Vector2f center, float distance, float thickness, float proportion, sf::Uint32 color)
{
    init(center, distance, thickness, proportion, color);
}

void RingShape::init(sf::Vector2f center, float distance, float thickness, float proportion, sf::Uint32 color)
{
    color_ = sf::Color(color);
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

void RingShape::draw(sf::RenderTarget & window)
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

void RingShape::setCenter(sf::Vector2f center) {
    center_ = center;
    update();
}

void RingShape::setFillColor(sf::Uint32 fillColor) {
    color_ = sf::Color(fillColor);
    update();
}


RingShapeOutline::RingShapeOutline(sf::Vector2f center, float distance, float thickness, float proportion, float outline) : 
    center_(center, distance, thickness, proportion),
    borderUp_(center, distance + thickness, outline, proportion), 
    borderDown_(center, distance - outline, outline, proportion)

{
    proportion_ = proportion;
    outlineThickness_ = outline;
    distance_ = distance;
}

void RingShapeOutline::setDistance(float distance)
{
    center_.setDistance(distance);
    borderUp_.setDistance(distance + proportion_);
    borderDown_.setDistance(distance - outlineThickness_);
}

void RingShapeOutline::addDistance(float delta)
{
    center_.addDistance(delta);
    borderUp_.addDistance(delta);
    borderDown_.addDistance(delta);
}

void RingShapeOutline::setThickness(float thick)
{
    center_.setThickness(thick);
    borderUp_.setDistance(distance_ + thick);
}

void RingShapeOutline::setAlpha(float alpha)
{
    center_.setAlpha(alpha);
    borderUp_.setAlpha(alpha);
    borderDown_.setAlpha(alpha);
}

void RingShapeOutline::setProportion(float proportion)
{
    center_.setProportion(proportion);
    borderUp_.setProportion(proportion);
    borderDown_.setProportion(proportion);
}

void RingShapeOutline::setCenter(sf::Vector2f center)
{
    center_.setCenter(center);
    borderUp_.setCenter(center);
    borderDown_.setCenter(center);
}

void RingShapeOutline::draw(sf::RenderTarget& window)
{
    center_.draw(window);
    borderUp_.draw(window);
    borderDown_.draw(window);
}

void RingShapeOutline::setFillColor(sf::Uint32 fillColor)
{
    center_.setFillColor(fillColor);
}

void RingShapeOutline::setOutlineColor(sf::Uint32 outlineColor)
{
    borderDown_.setFillColor(outlineColor);
    borderUp_.setFillColor(outlineColor);
}
