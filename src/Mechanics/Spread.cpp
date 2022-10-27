//
// Created by cyril on 30/05/2022.
//

#include "Spread.h"
#include "../System/Utils.h"

#include <cmath>
#include <iostream>

Spread::Spread(float beat, float radius, int nbShare, float active, const Target &target, DebuffType debuffToApply, float debuffTimer) :
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

    debuffToApply_ = debuffToApply;
    debuffTimer_ = debuffTimer;

    setColor();


    base_.setRadius(radius_);

    base_.setOutlineThickness(5);
    base_.setPointCount(100);

    Mechanic::setSoundName("Sound/normal-hitnormal.wav");

    drawPriority_ = target_.timing == TARGET_FOLLOW ? 15: isShare_ ? 10 : 0;

    highlightTimer_ = sf::seconds(0);
    highlight_ = false;
}

void Spread::onDraw(const sf::Time &elapsed, sf::RenderTarget &window) {
    if(draw_) {
        if (isFailed()) {
            backColor_.setSpeed({ 0.5, 0.5, 0.5, 0.5 });
            highlightTimer_ += elapsed;
            backColor_.updateColor(elapsed);
            if (highlightTimer_.asSeconds() > 1) {
                highlightTimer_ = sf::seconds(0);
                backColor_.setCurrentTarget(highlight_ ? "failed" : "hightlight");
                highlight_ = !highlight_;
            }
        }
        approachCircle_.draw(window);
        base_.setFillColor(backColor_.getCurrentColor());
        window.draw(base_);
        playerIndicator_.draw(window);
    }
}

void Spread::onCheck(const sf::Time &elapsed, float currentBeat, float cuurentPart, EntityManager &entities) {
    nbIn_ = 0;

    //std::cout << entities.getSizePlayers() << std::endl;
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

    //if(isShare_) {
        if(passed_ || earlypassed_) {
            backColor_.setCurrentTarget("good");
        }
        else {
            backColor_.setCurrentTarget("failed");
        }
        backColor_.updateColor(elapsed);
    //}

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
    if(target_.timing == TARGET_ONBEAT) {
        updatePosition(entities);
    }

    if (debuffToApply_ != DEBUFF_NONE) {
        for (int i = 0; i < entities.getSizePlayers(); i++) {
            Target t(TARGET_ENTITY, TARGET_PLAYERS, i);
            if (!entities.getActive(t))
                break;

            bool good = Utils::distance(entities.getPosition(t), position_) < radius_;

            if (good) {
                entities.applyDebuff(currentBeat, t, debuffToApply_, currentBeat + debuffTimer_);
            }
        }
    }
}

void Spread::onFade(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    approachCircle_.setProportion(1);

    sf::Color color = base_.getFillColor();
    color = base_.getOutlineColor();
    color.a = 255*(1-currentPart);
    base_.setOutlineColor(color);

    approachCircle_.setAlpha(255*(1-currentPart));

    backColor_.setCurrentColor(3, 255 * (1 - currentPart));

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

void Spread::reset(float beat) {

    setColor();

    target_.reset();

    base_.setRadius(radius_);
    base_.setPosition(position_.x - radius_, position_.y - radius_);
    approachCircle_.setDistance(radius_ + 10);
    backColor_.setSpeed({ 0.1, 0.1, 0.1, 0.5 });


    Mechanic::reset(beat);
}

void Spread::getTargetPos(std::vector<sf::Vector2f>& pos)
{
    pos.emplace_back(position_);
}

void Spread::setTargetPos(std::vector<sf::Vector2f>& pos)
{
    if (pos.size() != 1) {
        std::cout << "Spread::setTargetPos : pos vector is wrong size." << std::endl;
        return;
    }

    target_.type = TargetType::TARGET_POS;
    target_.pos = pos[0];
}

void Spread::setColor() {
    sf::Uint32 outlineColor=0, fillColorPlayerIndicator=0, fillColor=0, fillColorFailed=0, approachColor=0;

    if(isShare_) {
        if(target_.timing == TARGET_FOLLOW && nbShare_ == 1 && target_.team == TARGET_PLAYERS) {
            outlineColor = 0xFFD5CBFF;
            fillColor = 0xB64F3860;
            fillColorFailed = 0x781F0B60;
            fillColorPlayerIndicator = 0xFFD5CB00;
            approachColor = 0xD35227FF;
        }
        else if (target_.type == TARGET_POS) {
            outlineColor = 0xDAFB93FF;
            fillColor = 0x89C17EBB;
            fillColorFailed = 0x427538BB;
            fillColorPlayerIndicator = 0xDAFB9300;
            approachColor = 0x79CE1BFF;
        }
        else {
            outlineColor = 0xDAFB93FF;
            fillColor = 0x89C17E60;
            fillColorFailed = 0x42753860;
            fillColorPlayerIndicator = 0xDAFB9300;
            approachColor = 0x79CE1BFF;
        }
    }
    else {
        outlineColor = 0xFFD5CBFF;
        fillColor = 0xB64F38BB;
        fillColorFailed = 0x781F0BBB;
        fillColorPlayerIndicator = 0xFFD5CB00;
        approachColor = 0xD35227FF;
    }

    backColor_.setSpeed({0.1, 0.1, 0.1, 0.5});

    approachCircle_.setFillColor(approachColor);
    playerIndicator_.setOutlineColor(outlineColor);
    playerIndicator_.setFillColor(fillColorPlayerIndicator);
    backColor_.addTarget("good", fillColor);
    backColor_.addTarget("failed", fillColorFailed);

    backColor_.addTarget("hightlight", 0xe8bb00ff);

    backColor_.initCurrent("failed");
    base_.setOutlineColor(sf::Color(outlineColor));
}

std::string Spread::toString() {
    std::string res;

    res = "SPREAD," + std::to_string(beat_) + "," + std::to_string(nbShare_) + "," +
            std::to_string(radius_) + "," + std::to_string(active_) + "," +
            std::to_string(debuffToApply_) + "," + std::to_string(debuffTimer_) + ",";

    res += target_.to_string();

    return res;
}

Mechanic* Spread::clone()
{
    return new Spread(*this);
}
