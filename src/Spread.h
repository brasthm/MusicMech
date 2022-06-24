//
// Created by cyril on 30/05/2022.
//

#ifndef MUSICMECH_CLIENT_SPREAD_H
#define MUSICMECH_CLIENT_SPREAD_H

#include "Mechanic.h"
#include "PlayerIndicator.h"
#include "RingShape.h"
#include "ShiftColor.h"


class Spread : public Mechanic {
    sf::CircleShape base_;
    PlayerIndicator playerIndicator_;
    RingShape approachCircle_;
    sf::Vector2f position_;
    float radius_, newRadius_;
    int nbShare_, nbIn_;
    Joueur *joueurCible_;
    bool follow_;
    ShiftColor backColor_;


public:
    Spread(float beat, sf::Vector2f position, float radius, float nbShare, float active, Joueur * joueurCible);
    void onDraw(const sf::Time &elapsed, sf::RenderWindow &window) override;
    void onCheck(const sf::Time &elapsed, std::vector<Joueur> &joueurs) override;
    void onApproach(const sf::Time &elapsed, float currentBeat, float cuurentPart, std::vector<Joueur> &joueurs) override;
    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) override;
    void onFade(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) override;
};


#endif //MUSICMECH_CLIENT_SPREAD_H
