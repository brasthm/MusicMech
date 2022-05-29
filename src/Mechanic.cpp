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
    played_ = checked_ = passed_ = draw_ = false;
    alpha_ = 255;
    active_ = 4;
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

void Mechanic::update(const sf::Time &elapsed, float currentBeat, std::vector<Joueur> &joueurs) {
    float n = std::abs(currentBeat - beat_);
    float currentPart = n - (int)n;

    if(currentBeat < beat_)
        currentPart = 1-currentPart;

    if(beat_ > currentBeat && beat_ - currentBeat <= active_) {
        draw_ = true;

        onCheck(joueurs);
        updateColor(elapsed);

        onApproach(currentBeat, currentPart, joueurs);
    }
    else if(currentBeat > beat_ && currentBeat - beat_ <= 1) {
        draw_ = true;

        if(!checked_ && currentPart < 0.25) {
            onCheck(joueurs);
            updateColor(elapsed);
        }

        if(!checked_ && passed_) {
            playSound();
            onPassed(currentBeat, currentPart, joueurs);

            checked_ = true;
        }

        if(!checked_ && !passed_ && currentPart > 0.25) {
            onFailed(currentBeat, currentPart, joueurs);
            checked_ = true;
        }

        onFade(currentBeat, currentPart, joueurs);
    }
    else {
        draw_ = false;
    }

}

void Mechanic::draw(sf::RenderWindow &window) {
    onDraw(window);
}
