//
// Created by cyril on 12/06/2022.
//

#include "Tether.h"

#include "../System/Utils.h"
#include "../main.h"
#include <cmath>
#include <iostream>

Tether::Tether(float beat, Joueur *anchor1, Joueur *anchor2, float minDist, float active, bool inward, bool continu) {
    anchor1_ = anchor1;
    anchor2_ = anchor2;
    beat_ = beat;
    minDist_ = minDist;
    active_ = active;
    drawArrow_ = true;
    drawPriority_ = 100;

    inward_ = inward;
    continu_ = continu;

    backColor_.addTarget("passed", 0x89CA7EFF);
    backColor_.addTarget("failed", 0xB64F38FF);
    backColor_.setSpeed({360, 1, 1, 1});
    backColor_.initCurrent("failed");

    borderColor_.addTarget("passed", 0xDAFB93FF);
    borderColor_.addTarget("failed", 0xFFD5CBFF);
    borderColor_.setSpeed({360, 1, 1, 1});
    borderColor_.initCurrent("failed");

    indicatorColor_.addTarget("passed", 0x79CE1BFF);
    indicatorColor_.addTarget("failed", 0xD35227FF);
    indicatorColor_.setSpeed({360, 1, 1, 1});
    indicatorColor_.initCurrent("failed");

    tether_.setOutlineThickness(5);
    tether_.setSize({100, 10});
    tether_.setOrigin({0, 5});

    indicator_.setOrigin({0, 15});
    indicator_.setSize({100, 40});

    arr1.setScale(1.5);
    arr2.setScale(1.5);

    arr1.setColorSpeed({1,1,1, 255});
    arr2.setColorSpeed({1,1,1, 255});

    Mechanic::setSoundName("Sound/normal-hitnormal.wav");
}

void Tether::onDraw(const sf::Time &elapsed, sf::RenderWindow &window) {
    if(draw_) {
        tether_.setFillColor(backColor_.getCurrentColor());
        tether_.setOutlineColor(borderColor_.getCurrentColor());
        indicator_.setFillColor(indicatorColor_.getCurrentColor());
        window.draw(indicator_);
        window.draw(tether_);
        if(drawArrow_){
            arr1.draw(window);
            arr2.draw(window);
        }
    }
}

void Tether::onCheck(const sf::Time &elapsed, std::vector<Joueur> &joueurs) {
    bool good;

    if(inward_) good = Utils::distance(anchor1_->getPos(), anchor2_->getPos()) <= minDist_;
    else good = Utils::distance(anchor1_->getPos(), anchor2_->getPos()) >= minDist_;

    if(good) {
        passed_ = true;
        borderColor_.setCurrentTarget("passed");
        backColor_.setCurrentTarget("passed");
        indicatorColor_.setCurrentTarget("passed");
    }
    else {
        passed_ = false;
        borderColor_.setCurrentTarget("failed");
        backColor_.setCurrentTarget("failed");
        indicatorColor_.setCurrentTarget("failed");
    }
    borderColor_.updateColor(elapsed);
    backColor_.updateColor(elapsed);
    indicatorColor_.updateColor(elapsed);
}

void Tether::onApproach(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
    auto d = (float)Utils::distance(anchor1_->getPos(), anchor2_->getPos());
    tether_.setSize({d, 10});
    sf::Vector2f dir = (anchor2_->getPos() - anchor1_->getPos())/d;
    float signX = anchor2_->getPosX() - anchor1_->getPosX() > 0 ? 1:-1;
    float signY = anchor2_->getPosY() - anchor1_->getPosY() > 0 ? 1:-1;

    float angle = 0;

    if(anchor2_->getPosX() - anchor1_->getPosX() > 0) {
        tether_.setPosition(anchor1_->getPos());
        angle = std::atan((float)(anchor2_->getPosY() - anchor1_->getPosY())/
                          (float)(anchor2_->getPosX() - anchor1_->getPosX()));
    }
    else {
        tether_.setPosition(anchor2_->getPos());
        angle = std::atan((float)(anchor1_->getPosY() - anchor2_->getPosY())/
                          (float)(anchor1_->getPosX() - anchor2_->getPosX()));
    }

    indicator_.setRotation(0);

    angle = 180 * angle / PI;
    tether_.setRotation(angle);

    if(continu_) {
        float position = 2*d*currentPart - d;
        float width = 0;

        if(position <= 0) {
            indicator_.setSize({position + d, 40});
            indicator_.setOrigin(0, 20);
            if(signX == 1) indicator_.setPosition(anchor1_->getPos());
            else indicator_.setPosition(anchor2_->getPos());
        }
        else {
            indicator_.setSize({d-position, 40});
            indicator_.setOrigin(0, 20);
            if(signX == 1) indicator_.setPosition(anchor1_->getPos() + position*dir);
            else indicator_.setPosition(anchor2_->getPos() - position*dir);
        }
    }
    else {
        float proportion = 1.f/active_ * (active_ - std::floor(beat_ - currentBeat + 1));
        if(currentPart > 0.66) {
            proportion += 1.f/active_ * (currentPart - 0.66)/0.34;
        }

        indicator_.setSize({proportion*d, 40});
        indicator_.setOrigin(proportion*d/2, 20);
        indicator_.setPosition((anchor1_->getPos() + anchor2_->getPos())/2.f);
    }

    indicator_.setRotation(angle);

    float prop = arr1.getWidth();

    drawArrow_ = prop < d;

    arr1.setRotation(angle);
    arr2.setRotation(angle+180);

    if(inward_) {
        arr1.setPosition((anchor1_->getPos()+anchor2_->getPos())*0.5f - signX*(1-currentPart)*(d-prop)*0.5f*dir);
        arr2.setPosition((anchor1_->getPos()+anchor2_->getPos())*0.5f + signX*(1-currentPart)*(d-prop)*0.5f*dir);
    }
    else {
        arr1.setPosition((anchor1_->getPos()+anchor2_->getPos())*0.5f + signX*dir*prop + signX*currentPart*(d-prop)*0.5f*dir);
        arr2.setPosition((anchor1_->getPos()+anchor2_->getPos())*0.5f - signX*dir*prop - signX*currentPart*(d-prop)*0.5f*dir);
    }


    arr1.update(elapsed);
    arr2.update(elapsed);
}

void Tether::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
}

void Tether::onFade(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {
    backColor_.setCurrentColor(3, 255*(1-currentPart));
    borderColor_.setCurrentColor(3, 255*(1-currentPart));
    indicatorColor_.setCurrentColor(3, 255*(1-currentPart));
    drawArrow_ = false;
}

