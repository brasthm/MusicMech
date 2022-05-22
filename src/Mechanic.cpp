//
// Created by cyril on 21/05/2022.
//

#include "Mechanic.h"
#include "DJ.h"

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
