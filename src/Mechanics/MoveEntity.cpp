//
// Created by cyril on 27/06/2022.
//

#include "MoveEntity.h"

MoveEntity::MoveEntity(float beat, const Target& entity, const Target& target, float speed, bool isInstant) : entity_(entity), target_(target){
    beat_ = beat;
    passed_ = true;
    speed_ = speed;
    isInstant_ = isInstant;
}

void MoveEntity::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    entities.setTargetPosition(entity_, target_, speed_, isInstant_);
}

std::string MoveEntity::toString() {
    std::string res;
    res = "MOVE," + std::to_string(beat_) + "," + std::to_string(speed_) + "," + std::to_string(isInstant_) + ",";
    res += entity_.to_string() + "," + target_.to_string();

    return res;
}
