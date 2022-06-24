//
// Created by cyril on 12/06/2022.
//

#ifndef MUSICMECH_CLIENT_TETHER_H
#define MUSICMECH_CLIENT_TETHER_H

#include "Mechanic.h"
#include "ShiftColor.h"
#include "ArrowShape.h"

class Tether : public Mechanic {
    Joueur *anchor1_, *anchor2_;
    float minDist_;
    sf::RectangleShape tether_, indicator_;
    ShiftColor borderColor_, backColor_, indicatorColor_;
    bool drawArrow_;

    bool inward_, continu_;

    ArrowShape arr1, arr2;

public:
    Tether(float beat, Joueur* anchor1, Joueur* anchor2, float minDist, float active, bool inward, bool continu);
    void onDraw(const sf::Time &elapsed, sf::RenderWindow &window) override;
    void onCheck(const sf::Time &elapsed, std::vector<Joueur> &joueurs) override;
    void onApproach(const sf::Time &elapsed, float currentBeat, float cuurentPart, std::vector<Joueur> &joueurs) override;
    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) override;
    void onFade(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) override;


    inline std::string toString() override {
        std::string s;
        s = "Tether out (beat: " + std::to_string(beat_) +
                ", player1: (" + std::to_string(anchor1_->getPosX()) + "," + std::to_string(anchor1_->getPosY())
                + "), player2: " + std::to_string(anchor2_->getPosX()) + "," + std::to_string(anchor2_->getPosY())  + ")";
        return s;
    }
};

inline std::ostream& operator <<(std::ostream& stream, Tether& tower) {
    return stream << tower.toString();
}


#endif //MUSICMECH_CLIENT_TETHER_H
