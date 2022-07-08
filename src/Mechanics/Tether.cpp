//
// Created by cyril on 12/06/2022.
//

#include "Tether.h"

#include "../System/Utils.h"
#include "../main.h"
#include <cmath>
#include <iostream>

Tether::Tether(float beat, const Target& t1, const Target& t2, float minDist, float active, bool inward, bool continu) : anchor1_(t1), anchor2_(t2) {
    beat_ = beat;
    minDist_ = minDist;
    active_ = active;
    drawArrow_ = true;
    drawPriority_ = 100;

    inward_ = inward;
    continu_ = continu;

    backColor_.addTarget("passed", 0x89CA7EFF);
    backColor_.addTarget("failed", 0xB64F38FF);
    backColor_.setSpeed({0.5, 0.5, 0.5, 0.5});
    backColor_.initCurrent("failed");

    borderColor_.addTarget("passed", 0xDAFB93FF);
    borderColor_.addTarget("failed", 0xFFD5CBFF);
    borderColor_.setSpeed({0.5, 0.5, 0.5, 0.5});
    borderColor_.initCurrent("failed");

    indicatorColor_.addTarget("passed", 0x79CE1BFF);
    indicatorColor_.addTarget("failed", 0xD35227FF);
    indicatorColor_.setSpeed({0.5, 0.5, 0.5, 0.5});
    indicatorColor_.initCurrent("failed");

    tether_.setOutlineThickness(5);
    tether_.setSize({100, 10});
    tether_.setOrigin({0, 5});

    indicator_.setOrigin({0, 15});
    indicator_.setSize({100, 40});

    arr1.setScale(1.5);
    arr2.setScale(1.5);

    arr1.setColorSpeed({1,1,1, 1});
    arr2.setColorSpeed({1,1,1, 1});

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

void Tether::onCheck(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &em) {
    bool good;

    if(inward_) good = Utils::distance(pos1_, pos2_) <= minDist_;
    else good = Utils::distance(pos1_, pos2_) >= minDist_;

    if(good) {
        timer_ = sf::seconds(0);
        passed_ = true;
        borderColor_.setCurrentTarget("passed");
        backColor_.setCurrentTarget("passed");
        indicatorColor_.setCurrentTarget("passed");
    }
    else {
        if(continu_) {
            float mercy = active_ > 16 ? 4:2;
            if(currentBeat > beat_ - active_ + mercy)
                timer_ += elapsed;
            if(timer_ >= sf::seconds(1))
                checked_ = true;
        }
        passed_ = false;
        borderColor_.setCurrentTarget("failed");
        backColor_.setCurrentTarget("failed");
        indicatorColor_.setCurrentTarget("failed");
    }
    borderColor_.updateColor(elapsed);
    backColor_.updateColor(elapsed);
    indicatorColor_.updateColor(elapsed);
}

void Tether::onApproach(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &em) {
    
    pos1_ = em.getPosition(anchor1_);
    pos2_ = em.getPosition(anchor2_);
    
    
    
    auto d = (float)Utils::distance(pos1_, pos2_);
    tether_.setSize({d, 10});
    sf::Vector2f dir = (pos2_ - pos1_)/d;
    float signX = pos2_.x - pos1_.x > 0 ? 1:-1;

    float angle = 0;

    if(signX == 1) {
        tether_.setPosition(pos1_);
        angle = std::atan((float)(pos2_.y - pos1_.y)/
                          (float)(pos2_.x - pos1_.x));
    }
    else {
        tether_.setPosition(pos2_);
        angle = std::atan((float)(pos1_.y - pos2_.y)/
                          (float)(pos1_.x - pos2_.x));
    }

    indicator_.setRotation(0);

    angle = 180 * angle / PI;
    tether_.setRotation(angle);

    if(continu_) {
        float position = 2*d*currentPart - d;

        if(position <= 0) {
            indicator_.setSize({position + d, 40});
            indicator_.setOrigin(0, 20);
            if(signX == 1) indicator_.setPosition(pos1_);
            else indicator_.setPosition(pos2_);
        }
        else {
            indicator_.setSize({d-position, 40});
            indicator_.setOrigin(0, 20);
            if(signX == 1) indicator_.setPosition(pos1_ + position*dir);
            else indicator_.setPosition(pos2_ - position*dir);
        }
    }
    else {
        float proportion = 1.f/active_ * (active_ - std::floor(beat_ - currentBeat + 1));
        if(currentPart > 0.66) {
            proportion += 1.f/active_ * (currentPart - 0.66f)/0.34f;
        }

        indicator_.setSize({proportion*d, 40});
        indicator_.setOrigin(proportion*d/2, 20);
        indicator_.setPosition((pos1_ + pos2_)/2.f);
    }

    indicator_.setRotation(angle);

    float prop = arr1.getWidth();

    drawArrow_ = prop < d;

    arr1.setRotation(angle);
    arr2.setRotation(angle+180);

    if(inward_) {
        arr1.setPosition((pos1_+pos2_)*0.5f - signX*(1-currentPart)*(d-prop)*0.5f*dir);
        arr2.setPosition((pos1_+pos2_)*0.5f + signX*(1-currentPart)*(d-prop)*0.5f*dir);
    }
    else {
        arr1.setPosition((pos1_+pos2_)*0.5f + signX*dir*prop + signX*currentPart*(d-prop)*0.5f*dir);
        arr2.setPosition((pos1_+pos2_)*0.5f - signX*dir*prop - signX*currentPart*(d-prop)*0.5f*dir);
    }


    arr1.update(elapsed);
    arr2.update(elapsed);
}

void Tether::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &em) {
}

void Tether::onFade(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &em) {
    backColor_.setCurrentColor(3, 255*(1-currentPart));
    borderColor_.setCurrentColor(3, 255*(1-currentPart));
    indicatorColor_.setCurrentColor(3, 255*(1-currentPart));
    drawArrow_ = false;
}

void Tether::reset(float beat) {
    backColor_.setCurrentColor(3, 255);
    borderColor_.setCurrentColor(3, 255);
    indicatorColor_.setCurrentColor(3, 255);

    timer_ = sf::seconds(0);

    Mechanic::reset(beat);
}

