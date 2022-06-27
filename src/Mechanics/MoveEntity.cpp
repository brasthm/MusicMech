//
// Created by cyril on 27/06/2022.
//

#include "MoveEntity.h"

MoveEntity::MoveEntity(float beat, Entity *target, const sf::Vector2f &pos, float speed, bool isInstant) {
    beat_ = beat;
    passed_ = true;
    target_ = target;
    speed_ = speed;
    isInstant_ = isInstant;
    pos_ = pos;
}

void MoveEntity::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
    target_->setTarget(pos_, speed_, isInstant_);
}
