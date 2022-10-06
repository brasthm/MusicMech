#ifndef MUSICMECH_CLIENT_MOVEARENA_H
#define MUSICMECH_CLIENT_MOVEARENA_H

#include "Mechanic.h"


class MoveArena : public Mechanic {
    Target target_;
    float speed_;

public:
    MoveArena(float beat, const Target& target, float speed);
    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    std::string toString() override;

    Mechanic* clone() override;
};


#endif //MUSICMECH_CLIENT_APPLYDEBUFF_H
