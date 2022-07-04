//
// Created by cyril on 03/07/2022.
//

#ifndef MUSICMECH_CLIENT_APPLYDEBUFF_H
#define MUSICMECH_CLIENT_APPLYDEBUFF_H

#include "Mechanic.h"
#include "../System/Debuff.h"


class ApplyDebuff : public Mechanic{
    Target target_;
    DebuffType type_;
    float end_;

public:
    ApplyDebuff(float beat, const Target& target, DebuffType type, float duration);
    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) override;

};


#endif //MUSICMECH_CLIENT_APPLYDEBUFF_H
