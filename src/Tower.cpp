//
// Created by cyril on 21/05/2022.
//

#include "Tower.h"
#include "Utils.h"

Tower::Tower(float beat, sf::Vector2f position, float radius, float nbShare, float active) :
    approachCircle_(position, radius + 10, 20, 0){
        position_ = position;
        beat_ = beat;
        radius_ = radius;
        draw_=false;


        nbIn_ = 0;
        nbShare_ = nbShare;

        active_ = active;

        float c = radius_ * 0.195;
        float g = radius_ * 0.1;

        float step = (SQRT2*c + SQRT2*g)/2;

        sf::Vector2f pos0(position_.x, position.y + radius_*0.6f);

        for(int i = 0; i < nbShare_; i++) {
            lights_.emplace_back();

            lights_.back().setFillColor(sf::Color(0xDAFB9300));
            lights_.back().setOutlineThickness(2);
            lights_.back().setOutlineColor(sf::Color(0xDAFB93FF));

            lights_.back().setSize({c, c});
            lights_.back().setRotation(45);


            if(i == 0) {
                lights_.back().setPosition(pos0.x , pos0.y);
            }
            else if(i == 1) {
                lights_.back().setPosition(pos0.x - step, pos0.y - step);
            }
            else if(i == 2) {
                lights_.back().setPosition(pos0.x + step, pos0.y - step);
            }
            else if(i == 3) {
                lights_.back().setPosition(pos0.x, pos0.y - 2 * step);
            }
        }


        newRadius_ = radius_;

        colorGood_ = sf::Color(0x89CA7EFF);
        colorFailed_ = sf::Color(0x427538FF);

        colorCurrent_ = Utils::RGBtoHSV(colorFailed_);
        colorTarget_ = colorCurrent_;

        speedColor_ = {10, 1, 5};


        base_.setRadius(radius_);
        base_.setPosition(position_.x - radius_, position_.y - radius_);

        base_.setOutlineThickness(5);
        base_.setOutlineColor(sf::Color(0xDAFB93FF));
        base_.setPointCount(100);

        Mechanic::setSoundName("Sound/normal-hitnormal.wav");
}

void Tower::onDraw(sf::RenderWindow &window) {
    if(draw_) {
        approachCircle_.draw(window);
        sf::Color displayColor = Utils::HSVtoRGB(colorCurrent_);
        displayColor.a = alpha_;
        base_.setFillColor(displayColor);
        window.draw(base_);

        for(int i = 0; i < lights_.size(); i++) {
            window.draw(lights_[i]);
        }
    }

}


void Tower::onCheck(std::vector<Joueur> &joueurs) {

    nbIn_ = 0;


    for(int  i = 0; i < joueurs.size(); i++) {

        if(!joueurs[i].getConnected())
            break;

        bool good = Utils::distance(joueurs[i].getPos(), position_) < radius_;

        if(good) {
            nbIn_++;
        }
    }

    passed_ = nbIn_ >= nbShare_;

    if(passed_) {
        Mechanic::setColorTarget(colorGood_);
    }
    else {
        Mechanic::setColorTarget(colorFailed_);
    }

    for(int i = 0; i < lights_.size(); i++) {
        sf::Color c = lights_[i].getFillColor();
        c.a = i < nbIn_ ? 255:0;
        lights_[i].setFillColor(c);
    }


}

void Tower::onApproach(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
    if(currentPart > 0.66) {
        approachCircle_.setProportion(1.f/active_ * (active_ - (int)(beat_ - currentBeat + 1) + (currentPart - 0.66)/0.34));
    }
}

void Tower::onPassed(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
    newRadius_ = radius_ * (1 + 0.5 * (1 - currentPart));
}

void Tower::onFade(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
    approachCircle_.setProportion(1);

    sf::Color color = base_.getFillColor();
    color = base_.getOutlineColor();
    color.a = 255*(1-currentPart);
    base_.setOutlineColor(color);

    approachCircle_.setAlpha(255*(1-currentPart));

    alpha_ = 255*(1-currentPart);


    base_.setRadius(newRadius_);
    base_.setPosition(position_.x - newRadius_, position_.y - newRadius_);
    approachCircle_.setDistance(newRadius_);

    float c = newRadius_ * 0.195;
    float g = newRadius_ * 0.1;

    float step = (SQRT2*c + SQRT2*g)/2;

    sf::Vector2f pos0(position_.x, position_.y + newRadius_*0.6f);

    for(int i = 0; i < nbShare_; i++) {
        lights_.emplace_back();

        color = lights_[i].getFillColor();
        if(color.a != 0) {
            color.a = 255*(1-currentPart);
            lights_[i].setFillColor(color);
        }

        color = lights_[i].getOutlineColor();
        color.a = 255*(1-currentPart);
        lights_[i].setOutlineColor(color);

        lights_[i].setSize({c, c});


        if(i == 0) {
            lights_[i].setPosition(pos0.x , pos0.y);
        }
        else if(i == 1) {
            lights_[i].setPosition(pos0.x - step, pos0.y - step);
        }
        else if(i == 2) {
            lights_[i].setPosition(pos0.x + step, pos0.y - step);
        }
        else if(i == 3) {
            lights_[i].setPosition(pos0.x, pos0.y - 2 * step);
        }
    }
}
