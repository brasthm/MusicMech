//
// Created by cyril on 12/06/2022.
//

#ifndef MUSICMECH_CLIENT_TETHER_H
#define MUSICMECH_CLIENT_TETHER_H

#include "Mechanic.h"
#include "../Graphics/ShiftColor.h"
#include "../Graphics/ArrowShape.h"

class Tether : public Mechanic {
    Target anchor1_, anchor2_;
    sf::Vector2f pos1_, pos2_, shift1_, shift2_;
    float minDist_;
    sf::RectangleShape tether_, indicator_;
    ShiftColor borderColor_, backColor_, indicatorColor_;
    bool drawArrow_;
    sf::Time timer_, vibrate_;

    bool inward_, continu_;
    float min_;

    ArrowShape arr1, arr2;

public:
    Tether(float beat, const Target& t1, const Target& t2, float minDist, float active, bool inward, bool continu);
    void onDraw(const sf::Time &elapsed, sf::RenderTarget &window) override;
    void onCheck(const sf::Time &elapsed, float currentBeat, float cuurentPart, EntityManager &em) override;
    void onApproach(const sf::Time &elapsed, float currentBeat, float cuurentPart, EntityManager &em) override;
    void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &em) override;
    void onFade(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &em) override;
    void reset(float beat) override;

    std::string toString() override;

};

inline std::ostream& operator <<(std::ostream& stream, Tether& tower) {
    return stream << tower.toString();
}


#endif //MUSICMECH_CLIENT_TETHER_H
