#include "Donut.h"

#include "../System/Utils.h"
#include <cmath>

void Donut::updatePosition(EntityManager& entityManager)
{
    position_ = entityManager.getPosition(target_);

    base_.setCenter({ position_.x, position_.y});
    approachCircle_.setCenter(position_);
    playerIndicator_.updatePosition(position_);
}

void Donut::setColor()
{
    sf::Uint32 outlineColor = 0, fillColorPlayerIndicator = 0, fillColor = 0, fillColorFailed = 0, approachColor = 0;

    if (isShare_) {
        if (target_.timing == TARGET_FOLLOW && nbShare_ == 1 && target_.team == TARGET_PLAYERS) {
            outlineColor = 0xFFD5CBFF;
            fillColor = 0xB64F3840;
            fillColorFailed = 0x781F0B40;
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

    backColor_.setSpeed({ 0.1, 0.1, 0.1, 0.5 });

    approachCircle_.setFillColor(approachColor);
    playerIndicator_.setOutlineColor(outlineColor);
    playerIndicator_.setFillColor(fillColorPlayerIndicator);
    backColor_.addTarget("good", fillColor);
    backColor_.addTarget("failed", fillColorFailed);

    backColor_.initCurrent("failed");
    base_.setOutlineColor(outlineColor);

    outlineColor_ = sf::Color(outlineColor);
}

Donut::Donut(float beat, float distanceMin, float distanceMax, int nbShare, float active, const Target& target) :
    target_(target),
    approachCircle_({}, distanceMin - 50, 20, 0),
    base_({}, distanceMin, distanceMax - distanceMin, 1.f, 5),
    playerIndicator_({}, sf::Vector2f(0, - distanceMin - (distanceMax - distanceMin) * 0.25f), nbShare,
        (distanceMax - distanceMin)  * 0.15f, 10)
{
    beat_ = beat;
    distanceMin_ = distanceMin;
    distanceMax_ = distanceMax;
    draw_ = false;

    nbIn_ = 0;
    nbShare_ = nbShare;

    isShare_ = nbShare != 0;
    active_ = active;

    setColor();

    Mechanic::setSoundName("Sound/normal-hitnormal.wav");

    drawPriority_ = -1;
}

void Donut::onDraw(const sf::Time& elapsed, sf::RenderTarget& window)
{
    if(draw_) {
        approachCircle_.draw(window);
        base_.setFillColor(backColor_.getCurrentColor().toInteger());
        base_.draw(window);
        playerIndicator_.draw(window);
    }
}

void Donut::onCheck(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities)
{
    nbIn_ = 0;

    //std::cout << entities.getSizePlayers() << std::endl;
    for (int i = 0; i < entities.getSizePlayers(); i++) {
        Target t(TARGET_ENTITY, TARGET_PLAYERS, i);
        if (!entities.getActive(t))
            break;

        float dist = Utils::distance(entities.getPosition(t), position_);

        bool good = dist >= distanceMin_ && dist <= distanceMax_;

        if (good) {
            nbIn_++;
        }
    }

    passed_ = nbIn_ == nbShare_;

    //if (isShare_) {
        if (passed_ || earlypassed_) {
            backColor_.setCurrentTarget("good");
        }
        else {
            backColor_.setCurrentTarget("failed");
        }
        backColor_.updateColor(elapsed);
    //}

    playerIndicator_.updateLight(nbIn_);
}

void Donut::onApproach(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    if (currentPart > 0.66) {
        approachCircle_.setProportion(1.f / active_ * (active_ - std::floor(beat_ - currentBeat + 1) + (currentPart - 0.66f) / 0.34f));
    }
    else {
        approachCircle_.setProportion(1.f / active_ * (active_ - std::floor(beat_ - currentBeat + 1)));
    }

    if ((beat_ - currentBeat) <= 1 && currentPart > 0.9) {
        if (!isShare_) {
            backColor_.setCurrentTarget("good");
            backColor_.updateColor(elapsed);
        }

    }

    if (target_.timing == TARGET_FOLLOW) {
        updatePosition(entities);
    }
}

void Donut::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    if (target_.timing == TARGET_ONBEAT) {
        updatePosition(entities);
    }
}

void Donut::onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    approachCircle_.setProportion(1);

    sf::Color color;
    color = outlineColor_;
    color.a = 255 * (1 - currentPart);
    base_.setOutlineColor(color.toInteger());

    approachCircle_.setAlpha(255 * (1 - currentPart));
    backColor_.setCurrentColor(3, 255 * (1 - currentPart));

    playerIndicator_.updateAlpha(currentPart);
}

void Donut::onInit(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    if (target_.timing == TARGET_ONINIT) {
        updatePosition(entities);
    }
}

void Donut::reset(float beat)
{
    setColor();

    target_.reset();

    Mechanic::reset(beat);
}

std::string Donut::toString()
{
    std::string res;

    res = "DONUT," + std::to_string(beat_) + "," + std::to_string(nbShare_) + "," +
        std::to_string(distanceMin_) + "," + std::to_string(distanceMax_) + "," + std::to_string(active_) + ",";

    res += target_.to_string();

    return res;
}

Mechanic* Donut::clone()
{
    return new Donut(*this);
}
