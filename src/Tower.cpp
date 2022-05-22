//
// Created by cyril on 21/05/2022.
//

#include "Tower.h"
#include "Utils.h"

Tower::Tower(int beat, sf::Vector2f position, float radius) :
    approachCircle_(position, radius + 10, 20, 0){
        position_ = position;
        beat_ = beat;
        radius_ = radius;
        draw_=false;
        hitsound_=false;

        newRadius_ = radius_;

        base_.setRadius(radius_);
        base_.setPosition(position_.x - radius_, position_.y - radius_);
        base_.setFillColor(sf::Color::Blue);

        Mechanic::setSoundName("Sound/normal-hitnormal.wav");
}

void Tower::draw(sf::RenderWindow &window) {
    if(draw_) {
        approachCircle_.draw(window);
        window.draw(base_);
    }

}

void Tower::update(int currentBeat, float currentPart, sf::Vector2f pos) {

    if(beat_ > currentBeat && beat_ - currentBeat <= 4) {
        if(currentPart > 0.66) {
            approachCircle_.setProportion(0.25 * (4 - (beat_ - currentBeat)) + 0.25*(currentPart - 0.66)/0.34);
        }
        draw_ = true;
    }
    else if(beat_ == currentBeat) {

        if(!checked_ && currentPart < 0.25)
            check(pos);
        if(!checked_ && passed_) {
            Mechanic::playSound();
            newRadius_ = radius_ * (1 + 0.5 * (1 - currentPart));

            checked_ = false;
        }

        approachCircle_.setProportion(1);
        base_.setFillColor(sf::Color(0,0,255, 255*(1-currentPart)));
        approachCircle_.setAlpha(255*(1-currentPart));


        base_.setRadius(newRadius_);
        base_.setPosition(position_.x - newRadius_, position_.y - newRadius_);
        approachCircle_.setDistance(newRadius_);

    }
    else {
        draw_ = false;
    }

}

void Tower::check(sf::Vector2f pos) {
    passed_ = Utils::distance(pos, position_) < radius_;
}
