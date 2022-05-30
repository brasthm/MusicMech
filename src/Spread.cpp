//
// Created by cyril on 30/05/2022.
//

#include "Spread.h"
#include "Utils.h"

Spread::Spread(float beat, sf::Vector2f position, float radius, float nbShare, float active, Joueur *joueurCible) :
        approachCircle_(position, radius + 10, 20, 0, 0x781F0B88),
        playerIndicator_(sf::Vector2f(position.x, position.y), sf::Vector2f(0, radius*0.6f), nbShare,
                         0xFFD5CB88, 0xB64F3888,
                         radius * 0.195f, radius * 0.1f) {

    position_ = position;
    beat_ = beat;
    radius_ = radius;
    draw_=false;


    nbIn_ = 0;
    nbShare_ = nbShare;

    active_ = active;

    newRadius_ = radius_;

    colorGood_ = sf::Color(0xB64F3888);
    colorFailed_ = sf::Color(0x781F0B88);

    colorCurrent_ = Utils::RGBtoHSV(colorFailed_);
    colorTarget_ = colorCurrent_;

    speedColor_ = {100, 100, 100};

    base_.setRadius(radius_);
    base_.setPosition(position_.x - radius_, position_.y - radius_);

    base_.setOutlineThickness(5);
    base_.setOutlineColor(sf::Color(0xFFD5CB88));
    base_.setPointCount(100);

    Mechanic::setSoundName("Sound/normal-hitnormal.wav");

    joueurCible_ = joueurCible;
    if(joueurCible_ == nullptr)
        follow_ = false;
    else
        follow_ = true;

}

void Spread::onDraw(sf::RenderWindow &window) {
    if(draw_) {
        approachCircle_.draw(window);
        sf::Color displayColor = Utils::HSVtoRGB(colorCurrent_);
        displayColor.a = alpha_;
        base_.setFillColor(displayColor);
        window.draw(base_);
        playerIndicator_.draw(window);
    }
}

void Spread::onCheck(std::vector<Joueur> &joueurs) {
    nbIn_ = 0;

    for(int  i = 0; i < joueurs.size(); i++) {

        if(!joueurs[i].getConnected())
            break;

        bool good = Utils::distance(joueurs[i].getPos(), position_) < radius_;

        if(good) {
            nbIn_++;
        }
    }

    passed_ = nbIn_ == nbShare_;

    playerIndicator_.updateLight(nbIn_);
}

void Spread::onApproach(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
    if(currentPart > 0.66) {
        approachCircle_.setProportion(1.f/active_ * (active_ - (int)(beat_ - currentBeat + 1) + (currentPart - 0.66)/0.34));
    }
    else {
        approachCircle_.setProportion(1.f/active_ * (active_ - (int)(beat_ - currentBeat + 1)));
    }

    if((beat_ - currentBeat) <= 1 && currentPart > 0.95) {
        if(passed_) {
            Mechanic::setColorTarget(colorGood_);
        }
        else {
            Mechanic::setColorTarget(colorFailed_);
        }
    }

    if(follow_) {
        position_ = joueurCible_->getPos();

        base_.setPosition(position_.x - radius_, position_.y - radius_);
        approachCircle_.setCenter(position_);
        playerIndicator_.updatePosition(position_);
    }
}

void Spread::onPassed(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
    //newRadius_ = radius_ * (1 + 0.5 * (1 - currentPart));
}

void Spread::onFade(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {


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
