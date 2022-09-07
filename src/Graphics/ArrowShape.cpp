//
// Created by cyril on 23/06/2022.
//

#include "ArrowShape.h"
#include <cmath>
#include "../System/Utils.h"
#include "../main.h"

ArrowShape::ArrowShape() {
    position_=sf::Vector2f(0,0);

    up_.setSize(sf::Vector2f(30, 10));
    up_.setOrigin(30, 0);
    up_.setRotation(45);

    down_.setSize(sf::Vector2f(30, 10));
    down_.setOrigin(30, 10);
    down_.setRotation(-45);

    outlineUp_.setSize(sf::Vector2f(40, 20));
    outlineUp_.setOrigin(40, 0);
    outlineUp_.setRotation(45);

    outlineDown_.setSize(sf::Vector2f(40, 20));
    outlineDown_.setOrigin(40, 20);
    outlineDown_.setRotation(-45);


    scale_ = 1.f;
    rotation_ = 0.f;

    outlineUp_.setFillColor(sf::Color::Black);
    outlineDown_.setFillColor(sf::Color::Black);

    color_.addTarget("default", 0xFFFFFFFF);
    color_.initCurrent("default");

}

void ArrowShape::draw(sf::RenderTarget &window) {
    up_.setFillColor(color_.getCurrentColor());
    down_.setFillColor(color_.getCurrentColor());

    window.draw(outlineUp_);
    window.draw(outlineDown_);

    window.draw(up_);
    window.draw(down_);

    
}

void ArrowShape::update(const sf::Time &elapsed) {

    up_.setScale(scale_, scale_);
    down_.setScale(scale_, scale_);

    outlineUp_.setScale(scale_, scale_);
    outlineDown_.setScale(scale_, scale_);

    up_.setRotation(45 + rotation_);
    down_.setRotation(-45 + rotation_);

    outlineUp_.setRotation(45 + rotation_);
    outlineDown_.setRotation(-45 + rotation_);

    up_.setPosition(position_);
    down_.setPosition(position_);

    outlineUp_.setPosition(position_.x + std::sqrt(5 * 5 * 2) * scale_ * std::cos(rotation_ * PI / 180), position_.y + std::sqrt(5 * 5 * 2) * scale_ * std::sin(rotation_ * PI / 180));
    outlineDown_.setPosition(position_.x + std::sqrt(5 * 5 * 2) * scale_ * std::cos(rotation_ * PI / 180), position_.y + std::sqrt(5 * 5 * 2) * scale_ * std::sin(rotation_ * PI / 180));


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
    return scale_*(float)((40.)*std::cos(PI/4.));
}
