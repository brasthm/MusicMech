//
// Created by cyril on 26/06/2022.
//

#include "Totem.h"
#include "../main.h"
#include "../System/Utils.h"

#include <cmath>

Totem::Totem() {
    draw_ = true;
    active_ = false;
    radius_ = BASE_TOTEM_RADIUS;
    shape_.setRadius(radius_);
    shape_.setFillColor(sf::Color(sf::Color::White));
    shape_.setPointCount(100);
    shape_.setOrigin(radius_, radius_);
    pos_.x = 0; pos_.y = 0; targetPos_= pos_;
    speed_ = 700;
    baseSpeed_ = speed_;
}

void Totem::update(sf::Time elapsed, Arena* arena, float beat) {
    shape_.setOrigin(radius_, radius_);
    shape_.setRadius(radius_);
    sf::Vector2f vecDep;
    if(active_) {
        vecDep = targetPos_ - pos_;

        float length = std::sqrt(vecDep.x * vecDep.x + vecDep.y * vecDep.y);

        if(length != 0) {
            vecDep = vecDep / length;
            float diffX, diffY;
            diffX = vecDep.x;
            diffY = vecDep.y;

            pos_ += vecDep * speed_ * elapsed.asSeconds();

            float newDiffX, newDiffY;
            newDiffX = targetPos_.x - pos_.x;
            newDiffY = targetPos_.y - pos_.y;

            if (!Utils::sameSign(newDiffX, diffX))
                pos_.x = targetPos_.x;
            if (!Utils::sameSign(newDiffY, diffY))
                pos_.y = targetPos_.y;
        }

        serv_pos_ = pos_;
    }
}

void Totem::draw(sf::RenderTarget &window) {
    if(active_ && draw_) {
        shape_.setPosition(pos_);
        shape_.setFillColor(sf::Color(color_));
        window.draw(shape_);
    }
}
