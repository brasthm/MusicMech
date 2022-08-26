#ifndef MUSICMECH_CLIENT_REMOVEARENA_H
#define MUSICMECH_CLIENT_REMOVEARENA_H

#include "Mechanic.h"

class RemoveArena : public Mechanic {
    float index_;
public:
    RemoveArena(float beat, int index);

    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;

    std::string toString() override;
};

#endif