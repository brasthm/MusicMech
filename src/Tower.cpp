//
// Created by cyril on 21/05/2022.
//

#include "Tower.h"

Tower::Tower(int beat, sf::Vector2f position, float radius) :
    approachCircle_(position, radius + 10, 20, 0){
        position_ = position;
        beat_ = beat;
        radius_ = radius;
        draw_=false;

        base_.setRadius(radius_);
        base_.setPosition(position_.x - radius_, position_.y - radius_);
        base_.setFillColor(sf::Color::Blue);
}

void Tower::draw(sf::RenderWindow &window) {
    if(draw_) {
        approachCircle_.draw(window);
        window.draw(base_);
    }

}

void Tower::update(int currentBeat, float currentPart) {

    if(beat_ > currentBeat && beat_ - currentBeat <= 4) {
        if(currentPart > 0.75) {
            approachCircle_.setProportion(0.25 * (4 - (beat_ - currentBeat)) + 0.25*(currentPart - 0.75)/0.25);
        }
        draw_ = true;
    }
    else if(beat_ == currentBeat) {
        base_.setFillColor(sf::Color(0,0,255, 255*(1-currentPart)));
        approachCircle_.setAlpha(255*(1-currentPart));
    }
    else {
        draw_ = false;
    }

}
