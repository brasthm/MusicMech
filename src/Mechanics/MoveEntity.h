//
// Created by cyril on 27/06/2022.
//

#ifndef MUSICMECH_CLIENT_MOVEENTITY_H
#define MUSICMECH_CLIENT_MOVEENTITY_H

#include "Mechanic.h"
#include "../Entity/Entity.h"

class MoveEntity : public Mechanic {
    Entity *target_;
    sf::Vector2f pos_;
    bool isInstant_;
    float speed_;
public:
    MoveEntity(float beat, Entity* target, const sf::Vector2f &pos, float speed, bool isInstant);

    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) override;

};


#endif //MUSICMECH_CLIENT_MOVEENTITY_H
