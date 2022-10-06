#ifndef MUSICMECH_CLIENT_ZOOMARENA_H
#define MUSICMECH_CLIENT_ZOOMARENA_H

#include "Mechanic.h"

class ZoomArena : public Mechanic {
    float val_, speed_;
public:
    ZoomArena(float beat, float val, float speed);

    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;

    std::string toString() override;
    Mechanic* clone() override;
};

#endif