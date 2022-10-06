#ifndef MUSICMECH_CLIENT_ENDMAP_H
#define MUSICMECH_CLIENT_ENDMAP_H

#include "Mechanic.h"

class EndMap : public Mechanic {
    float index_;
public:
    EndMap(float beat);
    void onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities) override;
    std::string toString() override;
    Mechanic* clone() override;
};

#endif