//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_TOWER_H
#define MUSICMECH_CLIENT_TOWER_H

#include "Mechanic.h"
#include "RingShape.h"
#include "PlayerIndicator.h"

#include <vector>

class Tower : public Mechanic{
private:
    sf::CircleShape base_;
    PlayerIndicator playerIndicator_;
    RingShape approachCircle_;
    sf::Vector2f position_;
    float radius_, newRadius_;
    int nbShare_, nbIn_;
public:
    Tower(float beat, sf::Vector2f position, float radius, float nbShare, float active);
    void onDraw(sf::RenderWindow &window) override;
    void onCheck(std::vector<Joueur> &joueurs) override;
    void onApproach(float currentBeat, float cuurentPart, std::vector<Joueur> &joueurs) override;
    void onPassed(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) override;
    void onFade(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) override;


    inline std::string toString() override {
        std::string s;
        s = "Tower(beat: " + std::to_string(beat_) + ", pos: (" + std::to_string(position_.x) + "," + std::to_string(position_.y) + "), radius: " + std::to_string(radius_) + ")";
        return s;
    }
};

inline std::ostream& operator <<(std::ostream& stream, Tower& tower) {
    return stream << tower.toString();
}

#endif //MUSICMECH_CLIENT_TOWER_H
