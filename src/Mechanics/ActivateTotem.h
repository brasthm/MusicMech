//
// Created by cyril on 27/06/2022.
//

#ifndef MUSICMECH_CLIENT_ACTIVATETOTEM_H
#define MUSICMECH_CLIENT_ACTIVATETOTEM_H

#include "Mechanic.h"

class ActivateTotem : public Mechanic {
    Target target_;
    bool val_;
    sf::Uint32 color_;
public:
    ActivateTotem(float beat, const Target& target, bool val, sf::Uint32 color = 0xFFFFFFFF);

    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) override;
    Mechanic* clone() override;

    std::string toString() override;
};


#endif //MUSICMECH_CLIENT_ACTIVATETOTEM_H
