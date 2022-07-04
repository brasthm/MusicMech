//
// Created by cyril on 17/06/2022.
//

#include "ShiftColor.h"
#include "../System/Utils.h"

#include <iostream>

void ShiftColor::updateColor(const sf::Time &elapsed) {
    for(int i = 0; i < colorCurrent_.size(); i++) {
        float diff = colorTargets_[currentTarget_][i] - colorCurrent_[i];
        if(std::abs(diff) > 1e-3) {
            float speed = 100000.f;
            if(shiftTime_[i] != 0)
                speed = (colorTargets_[currentTarget_][i] - colorTargets_[prevTarget_][i])/shiftTime_[i];

            float deltaD = speed * elapsed.asSeconds();
            if(std::abs(deltaD) > std::abs(diff))
                deltaD = diff;
            colorCurrent_[i] += deltaD;
        }
    }

}

void ShiftColor::setSpeed(int index, float val) {
    shiftTime_[index] = val;
}

void ShiftColor::setSpeed(const std::array<float, 4> &time) {
    shiftTime_ = time;
}

void ShiftColor::addTarget(const std::string& key, sf::Uint32 color) {
    colorTargets_[key] = Utils::RGBtoHSV(sf::Color(color));
}

void ShiftColor::setCurrentTarget(const std::string& target) {
    if(target != currentTarget_) {
        prevTarget_ = currentTarget_;
        currentTarget_ = target;
    }
}

sf::Color ShiftColor::getCurrentColor() {
    return Utils::HSVtoRGB(colorCurrent_);
}

void ShiftColor::setCurrentColor(int index, float val) {
    colorCurrent_[index] = val;
}

void ShiftColor::initCurrent(const std::string &key) {
    currentTarget_ = key;
    prevTarget_ = key;
    colorCurrent_ = colorTargets_[key];
}
