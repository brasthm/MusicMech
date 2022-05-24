//
// Created by cyril on 21/05/2022.
//

#include "Mechanic.h"
#include "DJ.h"
#include "Utils.h"

#include <cmath>
#include <iostream>

Mechanic::Mechanic() {
    beat_ = 0;
    played_ = false;
}

void Mechanic::playSound() {
    if(!played_) {
        DJ::playSound(sound_);
        played_ = true;
    }
}

void Mechanic::setSoundName(const std::string& name) {
    sound_ = name;
}

void Mechanic::setColorTarget(const sf::Color &color) {
    colorTarget_ = Utils::RGBtoHSV(color);
}

void Mechanic::updateColor(const sf::Time &elapsed) {
    sf::Vector3f diff = colorTarget_ - colorCurrent_;
    sf::Vector3f bump = Utils::RGBtoHSV(colorGood_) - Utils::RGBtoHSV(colorFailed_);

    float numm = sqrt(bump.x * bump.x + bump.y * bump.y + bump.z * bump.z);

    sf::Vector3f v = diff/numm;

    v.x = v.x * speedColor_.x * elapsed.asSeconds();
    v.y = v.y * speedColor_.y * elapsed.asSeconds();
    v.z = v.z * speedColor_.z * elapsed.asSeconds();

    colorCurrent_ = colorCurrent_ + v;
}
