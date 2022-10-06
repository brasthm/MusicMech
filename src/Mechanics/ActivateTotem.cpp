//
// Created by cyril on 27/06/2022.
//

#include "ActivateTotem.h"

ActivateTotem::ActivateTotem(float beat, const Target& target, bool val, sf::Uint32 color) : target_(target){
    beat_ = beat;
    val_ = val;
    passed_ = true;
    color_ = color;
}

void ActivateTotem::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    entities.setActive(target_, val_, color_);
}

Mechanic* ActivateTotem::clone()
{
    return new ActivateTotem(*this);
}

std::string ActivateTotem::toString() {
    std::string res =  "ACTIVATE," + std::to_string(beat_) + "," + std::to_string(val_) + "," + std::to_string(color_) + ",";
    res += target_.to_string();

    return res;
}
