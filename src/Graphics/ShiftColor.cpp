//
// Created by cyril on 17/06/2022.
//

#include "ShiftColor.h"
#include "../System/Utils.h"

void ShiftColor::updateColor(const sf::Time &elapsed) {
    float numm = Utils::distance(colorTargets_[currentTarget_], colorTargets_[prevTarget_]);

    if(numm != 0) {
        for(int i = 0; i < colorCurrent_.size(); i++) {
            float diff = colorTargets_[currentTarget_][i] - colorCurrent_[i];
            colorCurrent_[i] += diff/numm * speedColor_[i] * elapsed.asSeconds();
            float newDiff = colorTargets_[currentTarget_][i] - colorCurrent_[i];
            if(!Utils::sameSign(diff, newDiff))
                colorCurrent_[i] = colorTargets_[currentTarget_][i];
        }
    }
}

void ShiftColor::setSpeed(int index, float val) {
    speedColor_[index] = val;
}

void ShiftColor::setSpeed(const std::array<float, 4> &speed) {
    speedColor_ = speed;
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
