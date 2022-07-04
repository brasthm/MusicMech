//
// Created by cyril on 03/07/2022.
//

#include "Debuff.h"
#include "../main.h"

Debuff::Debuff() {
    type_ = DEBUFF_NONE;
    end_ = 0;

    shape_.setRadius(2*BASE_PLAYER_RADIUS);
    shape_.setOrigin(2*BASE_PLAYER_RADIUS, 2*BASE_PLAYER_RADIUS);

    color_.addTarget("none", 0xFFFFFF00);
    color_.addTarget("root", 0x888888FF);
    color_.setSpeed({0.25, 0.25, 0.25, 0.25});
    color_.initCurrent("none");
}

void Debuff::update(sf::Time elapsed, float beat) {
    if(type_ != DEBUFF_NONE) {
        if(beat >= end_)
            type_ = DEBUFF_NONE;
    }

    switch(type_) {
        case DEBUFF_NONE:
            color_.setCurrentTarget("none");
            break;
        case DEBUFF_ROOT:
            color_.setCurrentTarget("root");
            break;
    }

    color_.updateColor(elapsed);
}

void Debuff::draw(sf::RenderWindow &window, sf::Vector2f position) {
    shape_.setFillColor(color_.getCurrentColor());
    shape_.setPosition(position);
    window.draw(shape_);
}

void Debuff::apply(DebuffType type, float end) {
    type_ = type;
    end_ = end;
}

DebuffType Debuff::type() {
    return type_;
}
