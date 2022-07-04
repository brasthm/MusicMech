//
// Created by cyril on 27/06/2022.
//

#include "ActivateTotem.h"

ActivateTotem::ActivateTotem(float beat, const Target& target, bool val) : target_(target){
    beat_ = beat;
    val_ = val;
    passed_ = true;
}

void ActivateTotem::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    entities.setActive(target_, val_);
}
