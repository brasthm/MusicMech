#ifndef MUSICMECH_CLIENT_CLEARENA_H
#define MUSICMECH_CLIENT_CLEARENA_H

#include "Mechanic.h"

class ClearArena : public Mechanic {
    float index_;
public:
    ClearArena(float beat);

    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    std::string toString() override;
};

#endif