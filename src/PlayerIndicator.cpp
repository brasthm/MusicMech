//
// Created by cyril on 30/05/2022.
//

#include "PlayerIndicator.h"
#include "main.h"

PlayerIndicator::PlayerIndicator(sf::Vector2f pos, int nbTot, sf::Uint32 outlineColor, sf::Uint32 fillColor, float c, float g) {
    position_ = pos;
    nbTot_ = nbTot;

    c_ = c;

    step_ = (SQRT2*c + SQRT2*g)/2;

    outlineColor_ = sf::Color(outlineColor);
    fillColor_ = sf::Color(fillColor);

    for(int i = 0; i < nbTot_; i++) {
        lights_.emplace_back();

        lights_.back().setFillColor(fillColor_);
        lights_.back().setOutlineThickness(2);
        lights_.back().setOutlineColor(outlineColor_);

        lights_.back().setSize({c_, c_});
        lights_.back().setRotation(45);
    }

    updatePosition();
}



void PlayerIndicator::updatePosition() {
    for(int i = 0; i < nbTot_; i++) {
        if(i == 0) {
            lights_[i].setPosition(position_.x , position_.y);
        }
        else if(i == 1) {
            lights_[i].setPosition(position_.x - step_, position_.y - step_);
        }
        else if(i == 2) {
            lights_[i].setPosition(position_.x + step_, position_.y - step_);
        }
        else if(i == 3) {
            lights_[i].setPosition(position_.x, position_.y - 2 * step_);
        }
    }
}

void PlayerIndicator::updateAlpha(float alpha) {
    for(int i = 0; i < nbTot_; i++) {
        sf::Color color = lights_[i].getFillColor();
        if (color.a != 0) {
            color.a = 255 * (1 - alpha);
            lights_[i].setFillColor(color);
        }

        color = lights_[i].getOutlineColor();
        color.a = 255 * (1 - alpha);
        lights_[i].setOutlineColor(color);
    }
}

void PlayerIndicator::draw(sf::RenderWindow &window) {
    for(int i = 0; i < lights_.size(); i++) {
        window.draw(lights_[i]);
    }
}

void PlayerIndicator::updateLight(int nb) {
    for(int i = 0; i < lights_.size(); i++) {
        sf::Color c = lights_[i].getFillColor();
        c.a = i < nb ? 255:0;
        lights_[i].setFillColor(c);
    }
}
