//
// Created by cyril on 27/06/2022.
//

#include "ActivateTotem.h"

ActivateTotem::ActivateTotem(float beat, Totem *target, bool val) {
    beat_ = beat;
    val_ = val;
    target_ = target;
    passed_ = true;
}

void
ActivateTotem::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
    target_->setActive(val_);
}
