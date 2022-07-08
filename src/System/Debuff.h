//
// Created by cyril on 03/07/2022.
//

#ifndef MUSICMECH_CLIENT_DEBUFF_H
#define MUSICMECH_CLIENT_DEBUFF_H


#include <SFML/Graphics.hpp>

#include "../Graphics/ShiftColor.h"


enum DebuffType {
    DEBUFF_NONE, DEBUFF_ROOT
};

class Debuff {
private:
    float end_;
    DebuffType type_;
    sf::CircleShape shape_;
    ShiftColor color_;
public:
    Debuff();
    void update(sf::Time elapsed, float beat);
    void draw(sf::RenderWindow &window, sf::Vector2f position);
    void apply(DebuffType, float end);
    void clense();
    DebuffType type();
};


#endif //MUSICMECH_CLIENT_DEBUFF_H
