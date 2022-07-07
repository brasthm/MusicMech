//
// Created by cyril on 30/05/2022.
//

#include "Spread.h"
#include "../System/Utils.h"

#include <cmath>
#include <iostream>

Spread::Spread(float beat, float radius, int nbShare, float active, const Target &target) :
        target_(target),
        approachCircle_({}, radius + 10, 20, 0),
        playerIndicator_({}, sf::Vector2f(0, radius*0.6f), nbShare,
                         radius * 0.195f, radius * 0.1f) {

    beat_ = beat;
    radius_ = radius;
    draw_ = false;

    nbIn_ = 0;
    nbShare_ = nbShare;

    isShare_ = nbShare != 0;
    active_ = active;
    newRadius_ = radius_;

    sf::Uint32 outlineColor=0, fillColorPlayerIndicator=0, fillColor=0, fillColorFailed=0, approachColor=0;

    if(isShare_) {
        if(target_.timing == TARGET_FOLLOW) {
            outlineColor = 0xDAFB9388;
            fillColor = 0x89CA7E88;
            fillColorFailed = 0x42753888;
            fillColorPlayerIndicator = 0xDAFB9300;
            approachColor = 0x79CE1B88;
        }
        else {
            outlineColor = 0xDAFB9388;
            fillColor = 0x89C17E88;
            fillColorFailed = 0x42753888;
            fillColorPlayerIndicator = 0xDAFB9300;
            approachColor = 0x79CE1B88;
        }
    }
    else {
        outlineColor = 0xFFD5CB88;
        fillColor = 0xB64F38FF;
        fillColorFailed = 0x781F0B88;
        fillColorPlayerIndicator = 0xFFD5CB00;
        approachColor = 0xD3522788;
    }

    backColor_.setSpeed({0.1, 0.1, 0.1, 0.5});

    approachCircle_.setFillColor(approachColor);
    playerIndicator_.setOutlineColor(outlineColor);
    playerIndicator_.setFillColor(fillColorPlayerIndicator);
    backColor_.addTarget("good", fillColor);
    backColor_.addTarget("failed", fillColorFailed);
    base_.setOutlineColor(sf::Color(outlineColor));


    backColor_.initCurrent("failed");

    base_.setRadius(radius_);

    base_.setOutlineThickness(5);
    base_.setPointCount(100);

    Mechanic::setSoundName("Sound/normal-hitnormal.wav");

    drawPriority_ = target_.timing == TARGET_FOLLOW ? 15: isShare_ ? 10 : 0;
}

void Spread::onDraw(const sf::Time &elapsed, sf::RenderWindow &window) {
    if(draw_) {
        approachCircle_.draw(window);
        base_.setFillColor(backColor_.getCurrentColor());
        window.draw(base_);
        playerIndicator_.draw(window);
    }
}

void Spread::onCheck(const sf::Time &elapsed, float currentBeat, float cuurentPart, EntityManager &entities) {
    nbIn_ = 0;

    for(int  i = 0; i < entities.getSizePlayers(); i++) {
        Target t(TARGET_ENTITY, TARGET_PLAYERS, i);
        if(!entities.getActive(t))
            break;

        bool good = Utils::distance(entities.getPosition(t), position_) < radius_;

        if(good) {
            nbIn_++;
        }
    }

    passed_ = nbIn_ == nbShare_;

    if(isShare_) {
        if(passed_) {
            backColor_.setCurrentTarget("good");
        }
        else {
            backColor_.setCurrentTarget("failed");
        }
        backColor_.updateColor(elapsed);
    }

    playerIndicator_.updateLight(nbIn_);
}


void Spread::onApproach(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    if(currentPart > 0.66) {
        approachCircle_.setProportion(1.f/active_ * (active_ - std::floor(beat_ - currentBeat + 1) + (currentPart - 0.66f)/0.34f));
    }
    else {
        approachCircle_.setProportion(1.f/active_ * (active_ - std::floor(beat_ - currentBeat + 1)));
    }

    if((beat_ - currentBeat) <= 1 && currentPart > 0.9) {
        if(!isShare_) {
            backColor_.setCurrentTarget("good");
            backColor_.updateColor(elapsed);
        }

    }

    if(target_.timing == TARGET_FOLLOW) {
        updatePosition(entities);
    }
}

void Spread::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    if(isShare_) newRadius_ = radius_ * (1.f + 0.5f * (1.f - currentPart));

    if(target_.timing == TARGET_ONBEAT) {
        updatePosition(entities);
    }
}

void Spread::onFade(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    approachCircle_.setProportion(1);

    sf::Color color = base_.getFillColor();
    color = base_.getOutlineColor();
    color.a = 255*(1-currentPart);
    base_.setOutlineColor(color);

    approachCircle_.setAlpha(255*(1-currentPart));

    backColor_.setCurrentColor(3, 255*(1-currentPart));

    base_.setRadius(newRadius_);
    base_.setPosition(position_.x - newRadius_, position_.y - newRadius_);
    approachCircle_.setDistance(newRadius_ + 10);

    playerIndicator_.updateAlpha(currentPart);
}

void Spread::onInit(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    if(target_.timing == TARGET_ONINIT) {
        updatePosition(entities);
    }
}

void Spread::updatePosition(EntityManager &entityManager) {
    position_ = entityManager.getPosition(target_);

    base_.setPosition(position_.x - radius_, position_.y - radius_);
    approachCircle_.setCenter(position_);
    playerIndicator_.updatePosition(position_);
}
