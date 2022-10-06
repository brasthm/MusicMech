#ifndef MUSICMECH_CLIENT_ROTATEARENA_H
#define MUSICMECH_CLIENT_ROTATEARENA_H

#include "Mechanic.h"

class RotateArena : public Mechanic {
    float val_, speed_;
public:
    RotateArena(float beat, float val, float speed);

    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;

    std::string toString() override;
    Mechanic* clone() override;
};




#endif