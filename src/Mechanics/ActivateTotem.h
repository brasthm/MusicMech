//
// Created by cyril on 27/06/2022.
//

#ifndef MUSICMECH_CLIENT_ACTIVATETOTEM_H
#define MUSICMECH_CLIENT_ACTIVATETOTEM_H

#include "Mechanic.h"
#include "../Entity/Totem.h"

class ActivateTotem : public Mechanic {
    Totem *target_;
    bool val_;
public:
    ActivateTotem(float beat, Totem* target, bool val);

    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) override;

};


#endif //MUSICMECH_CLIENT_ACTIVATETOTEM_H
