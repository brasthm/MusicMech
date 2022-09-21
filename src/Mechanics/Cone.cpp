#include "Cone.h"

#include "../System/Utils.h"
#include <cmath>

void Cone::updatePosition(EntityManager& entityManager)
{
    sf::Vector2f anchor = entityManager.getPosition(anchor_);
    sf::Vector2f center = entityManager.getPosition(center_);


    float delta_x = anchor.x - center.x;
    float delta_y = anchor.y - center.y;
    float theta_radians = std::atan2(delta_y, delta_x);
    float prevAngle = theta_radians - width_ / 2 * 0.01745329251;
    float nextAngle = theta_radians + width_ / 2 * 0.01745329251;


    sf::Vector2f prev = { distance_ * std::cos(prevAngle) , distance_ * std::sin(prevAngle) };
    sf::Vector2f next = { distance_ * std::cos(nextAngle) , distance_ * std::sin(nextAngle) };


    base_.setPoint(0, center);
    base_.setPoint(1, center + prev);
    base_.setPoint(2, center + next);

    approachCircle_.setCenter(anchor);
    playerIndicator_.updatePosition(anchor);
}

void Cone::setColor()
{
    sf::Uint32 outlineColor = 0, fillColorPlayerIndicator = 0, fillColor = 0, fillColorFailed = 0, approachColor = 0;

    if (isShare_) {
        if (anchor_.timing == TARGET_FOLLOW && nbShare_ == 1 && anchor_.team == TARGET_PLAYERS) {
            outlineColor = 0xFFD5CBFF;
            fillColor = 0xB64F3860;
            fillColorFailed = 0x781F0B60;
            fillColorPlayerIndicator = 0xFFD5CB00;
            approachColor = 0xD35227FF;
        }
        else if(anchor_.type == TARGET_POS){
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
        approachColor = 0xD35227BB;
    }

    backColor_.setSpeed({ 0.1, 0.1, 0.1, 0.5 });

    approachCircle_.setFillColor(approachColor);
    playerIndicator_.setOutlineColor(outlineColor);
    playerIndicator_.setFillColor(fillColorPlayerIndicator);
    backColor_.addTarget("good", fillColor);
    backColor_.addTarget("failed", fillColorFailed);

    backColor_.initCurrent("failed");
    base_.setOutlineColor(sf::Color(outlineColor));
}

Cone::Cone(float beat, float width, float distance, int nbShare, float active, const Target& center, const Target& anchor) :
    anchor_(anchor),
    center_(center), 
    approachCircle_({}, 120, 20, 0),
    playerIndicator_({}, sf::Vector2f(0, BASE_PLAYER_RADIUS + 6 ), nbShare,
        50, BASE_PLAYER_RADIUS * 2)
{

    width_ = width;
    distance_ = distance;


    beat_ = beat;
    draw_ = false;

    nbIn_ = 0;
    nbShare_ = nbShare;

    isShare_ = nbShare != 0;
    active_ = active;

    setColor();


    base_.setOutlineThickness(5);
    base_.setPointCount(3);

    Mechanic::setSoundName("Sound/normal-hitnormal.wav");

    drawPriority_ = 20;
}

void Cone::onDraw(const sf::Time& elapsed, sf::RenderTarget& window)
{
    if (draw_) {
        approachCircle_.draw(window);
        base_.setFillColor(backColor_.getCurrentColor());
        window.draw(base_);
        playerIndicator_.draw(window);
    }
}

void Cone::onCheck(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& entities)
{
    nbIn_ = 0;

    //std::cout << entities.getSizePlayers() << std::endl;
    for (int i = 0; i < entities.getSizePlayers(); i++) {
        Target t(TARGET_ENTITY, TARGET_PLAYERS, i);
        if (!entities.getActive(t))
            break;

        bool good = Utils::pointInTriangle(entities.getPosition(t), base_.getPoint(0), base_.getPoint(1), base_.getPoint(2));

        if (good) {
            nbIn_++;
        }
    }

    passed_ = nbIn_ == nbShare_;

    if (passed_ || earlypassed_) {
        backColor_.setCurrentTarget("good");
    }
    else {
        backColor_.setCurrentTarget("failed");
    }
    backColor_.updateColor(elapsed);
    

    playerIndicator_.updateLight(nbIn_);
}

void Cone::onApproach(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
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

    if (anchor_.timing == TARGET_FOLLOW || center_.timing == TARGET_FOLLOW) {
        updatePosition(entities);
    }
}

void Cone::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    if (anchor_.timing == TARGET_ONBEAT || center_.timing == TARGET_ONBEAT) {
        updatePosition(entities);
    }
}

void Cone::onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    approachCircle_.setProportion(1);

    sf::Color color = base_.getFillColor();
    color = base_.getOutlineColor();
    color.a = 255 * (1 - currentPart);
    base_.setOutlineColor(color);

    approachCircle_.setAlpha(255 * (1 - currentPart));

    backColor_.setCurrentColor(3, 255 * (1 - currentPart));

    playerIndicator_.updateAlpha(currentPart);
}

void Cone::onInit(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    if (anchor_.timing == TARGET_ONINIT || center_.timing == TARGET_ONINIT) {
        updatePosition(entities);
    }
}

void Cone::reset(float beat)
{
    setColor();

    anchor_.reset();
    center_.reset();


    Mechanic::reset(beat);
}

std::string Cone::toString()
{
    std::string res;

    res = "CONE," + std::to_string(beat_) + "," + std::to_string(nbShare_) + "," +
       std::to_string(width_) + "," + std::to_string(distance_) + "," + std::to_string(active_) + ",";

    res += center_.to_string() + ",";
    res += anchor_.to_string();

    return res;
}
