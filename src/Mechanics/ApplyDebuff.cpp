//
// Created by cyril on 03/07/2022.
//

#include "ApplyDebuff.h"

ApplyDebuff::ApplyDebuff(float beat, const Target& target, DebuffType type, float duration) : target_(target) {
    beat_ = beat;
    type_ = type;
    end_ = beat + duration;
    passed_ = true;
}

void ApplyDebuff::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    entities.applyDebuff(target_, type_, end_);
}
