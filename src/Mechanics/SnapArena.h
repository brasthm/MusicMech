#ifndef MUSICMECH_CLIENT_SNAPARENA_H
#define MUSICMECH_CLIENT_SNAPARENA_H

#include "Mechanic.h"


class SnapArena : public Mechanic {
    Target target_;

public:
    SnapArena(float beat, float active, const Target& target);
    void onApproach(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    std::string toString() override;
    Mechanic* clone() override;
};


#endif //MUSICMECH_CLIENT_APPLYDEBUFF_H
