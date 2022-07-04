//
// Created by cyril on 21/05/2022.
//

#include "Mechanic.h"
#include "../System/DJ.h"
#include "../System/Utils.h"

#include <cmath>
#include <iostream>

Mechanic::Mechanic() {
    beat_ = 0;
    played_ = checked_ = passed_ = draw_ = init_ = false;
    active_ = 4;
    drawPriority_ = 0;
}

void Mechanic::playSound() {
    if(!played_ && !sound_.empty()) {
        DJ::playSound(sound_);
        played_ = true;
    }
}

void Mechanic::setSoundName(const std::string& name) {
    sound_ = name;
}

void Mechanic::update(const sf::Time &elapsed, float currentBeat, EntityManager &entities) {
    float n = std::abs(currentBeat - beat_);
    float currentPart = n - std::floor(n);

    if(currentBeat < beat_)
        currentPart = 1-currentPart;

    if(beat_ > currentBeat && beat_ - currentBeat <= active_) {
        draw_ = true;

        if(!init_) {
            onInit(elapsed, currentBeat, currentPart, entities);
            init_ = true;
        }

        onCheck(elapsed, currentBeat, currentPart, entities);
        onApproach(elapsed, currentBeat, currentPart, entities);
    }
    else if(currentBeat > beat_ && currentBeat - beat_ < 1) {
        draw_ = true;

        if(!checked_ && currentPart < 0.25) {
            onCheck(elapsed, currentBeat, currentPart, entities);
        }

        if(!checked_ && passed_) {
            playSound();
            onPassed(elapsed, currentBeat, currentPart, entities);

            checked_ = true;
        }

        if(!checked_ && !passed_ && currentPart > 0.25) {
            onFailed(elapsed, currentBeat, currentPart, entities);
            checked_ = true;
        }

        onFade(elapsed, currentBeat, currentPart, entities);
    }
    else {
        draw_ = false;
    }

}

void Mechanic::draw(const sf::Time &elapsed, sf::RenderWindow &window) {
    onDraw(elapsed, window);
}

int Mechanic::getDrawPriority() const {
    return drawPriority_;
}

bool Mechanic::operator<(const Mechanic &mech) const {
    if(drawPriority_ == mech.getDrawPriority())
        return beat_ < mech.getBeat();
    return drawPriority_ < mech.getDrawPriority();
}

float Mechanic::getBeat() const {
    return beat_;
}

