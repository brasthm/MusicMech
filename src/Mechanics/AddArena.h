#ifndef MUSICMECH_CLIENT_ADDARENA_H
#define MUSICMECH_CLIENT_ADDARENA_H

#include "Mechanic.h"

class AddArena : public Mechanic {
    float x_, y_, w_, h_;
public:
    AddArena(float beat, float x, float y, float w, float h);

    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    Mechanic* clone() override;

    std::string toString() override;
};

#endif