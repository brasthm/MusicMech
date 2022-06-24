//
// Created by cyril on 23/06/2022.
//

#include "ArrowShape.h"
#include <cmath>
#include "Utils.h"

ArrowShape::ArrowShape() {
    position_=sf::Vector2f(0,0);

    up_.setSize(sf::Vector2f(30, 10));
    up_.setOrigin(30, 0);
    up_.setRotation(45);

    down_.setSize(sf::Vector2f(30, 10));
    down_.setOrigin(30, 10);
    down_.setRotation(-45);

    scale_ = 1.f;
    rotation_ = 0.f;

    color_.addTarget("default", 0xFFFFFFFF);
    color_.initCurrent("default");

}

void ArrowShape::draw(sf::RenderWindow &window) {
    up_.setFillColor(color_.getCurrentColor());
    down_.setFillColor(color_.getCurrentColor());

    window.draw(up_);
    window.draw(down_);
}

void ArrowShape::update(const sf::Time &elapsed) {
    up_.setPosition(position_);
    down_.setPosition(position_);

    up_.setScale(scale_, scale_);
    down_.setScale(scale_, scale_);

    up_.setRotation(45 + rotation_);
    down_.setRotation(-45 + rotation_);

    color_.updateColor(elapsed);
}

void ArrowShape::setPosition(sf::Vector2f pos) {
    position_ = pos;
}

void ArrowShape::setScale(float scale) {
    scale_ = scale;
}

void ArrowShape::setRotation(float rotation) {
    rotation_ = rotation;
}

void ArrowShape::addColor(const std::string &key, sf::Uint32 color) {
    color_.addTarget(key, color);
}

void ArrowShape::setCurrent(const std::string &key) {
    color_.setCurrentTarget(key);
}

void ArrowShape::setColorSpeed(const std::array<float, 4> &speed) {
    color_.setSpeed(speed);
}

float ArrowShape::getWidth() const {
    return scale_*(float)((40.)*std::cos(M_PI/4.));
}
