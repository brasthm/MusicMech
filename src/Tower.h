//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_TOWER_H
#define MUSICMECH_CLIENT_TOWER_H

#include "Mechanic.h"
#include "RingShape.h"

class Tower : public Mechanic{
private:
    sf::CircleShape base_;
    RingShape approachCircle_;
    sf::Vector2f position_;
    float radius_;
    bool draw_, hitsound_;
public:
    Tower(int beat, sf::Vector2f position, float radius);
    void draw(sf::RenderWindow &window) override;
    void update(int currentBeat, float currentPart) override;
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
