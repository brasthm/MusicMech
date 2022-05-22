//
// Created by cyril on 21/05/2022.
//

#include "Mechanic.h"
#include "RessourceLoader.h"

Mechanic::Mechanic() {
    beat_ = 0;
    played_ = false;
}

void Mechanic::playSound() {
    if(!played_) {
        sound_.play();
        played_ = true;
    }
}

void Mechanic::setSoundName(const std::string& name) {
    sound_.setBuffer(RessourceLoader::getSoundBuffer(name));
}
