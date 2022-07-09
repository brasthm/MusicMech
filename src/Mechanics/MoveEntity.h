//
// Created by cyril on 27/06/2022.
//

#ifndef MUSICMECH_CLIENT_MOVEENTITY_H
#define MUSICMECH_CLIENT_MOVEENTITY_H

#include "Mechanic.h"
#include "../Entity/Entity.h"

class MoveEntity : public Mechanic {
    Target entity_, target_;
    bool isInstant_;
    float speed_;
public:
    MoveEntity(float beat, const Target& entity, const Target& target, float speed, bool isInstant);

    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) override;

    std::string toString() override;
};


#endif //MUSICMECH_CLIENT_MOVEENTITY_H
