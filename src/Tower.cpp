//
// Created by cyril on 21/05/2022.
//

#include "Tower.h"
#include "Utils.h"

Tower::Tower(float beat, sf::Vector2f position, float radius, float nbShare, float active) :
    approachCircle_(position, radius + 10, 20, 0),
    playerIndicator_(sf::Vector2f(position.x, position.y + radius*0.6f), nbShare,
                     0xDAFB93FF, 0xDAFB9300,
                     radius * 0.195f, radius * 0.1f){
        position_ = position;
        beat_ = beat;
        radius_ = radius;
        draw_=false;


        nbIn_ = 0;
        nbShare_ = nbShare;

        active_ = active;

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
        playerIndicator_.draw(window);
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

    playerIndicator_.updateLight(nbIn_);
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

    playerIndicator_.updateAlpha(currentPart);
}
