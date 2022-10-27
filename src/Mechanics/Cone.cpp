#include "Cone.h"

#include "../System/Utils.h"
#include <cmath>
#include <iostream>

void Cone::updatePosition(EntityManager& entityManager)
{
    anchorPos_ = entityManager.getPosition(anchor_);
    centerPos_ = entityManager.getPosition(center_);


    float delta_x = anchorPos_.x - centerPos_.x;
    float delta_y = anchorPos_.y - centerPos_.y;
    float theta_radians = std::atan2(delta_y, delta_x);
    float prevAngle = theta_radians - width_ / 2 * 0.01745329251;
    float nextAngle = theta_radians + width_ / 2 * 0.01745329251;


    sf::Vector2f prev = { distance_ * std::cos(prevAngle) , distance_ * std::sin(prevAngle) };
    sf::Vector2f next = { distance_ * std::cos(nextAngle) , distance_ * std::sin(nextAngle) };


    base_.setPoint(0, centerPos_);
    base_.setPoint(1, centerPos_ + prev);
    base_.setPoint(2, centerPos_ + next);

    approachCircle_.setCenter(anchorPos_);
    playerIndicator_.updatePosition(centerPos_);
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
    backColor_.addTarget("hightlight", 0xe8bb00ff);

    backColor_.initCurrent("failed");
    base_.setOutlineColor(sf::Color(outlineColor));
}

Cone::Cone(float beat, float width, float distance, int nbShare, float active, const Target& center, const Target& anchor, DebuffType debuffToApply, float debuffTimer) :
    anchor_(anchor),
    center_(center), 
    approachCircle_({}, 120, 20, 0),
    playerIndicator_({}, sf::Vector2f(0, BASE_PLAYER_RADIUS + 6 ), nbShare,
        50, BASE_PLAYER_RADIUS * 2)
{

    width_ = width;
    distance_ = distance;

    debuffToApply_ = debuffToApply;
    debuffTimer_ = debuffTimer;


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

    highlightTimer_ = sf::seconds(0);
    highlight_ = false;
}

void Cone::onDraw(const sf::Time& elapsed, sf::RenderTarget& window)
{
    if (draw_) {
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

    for (int i = 0; i < entities.getSizePlayers(); i++) {
        Target t(TARGET_ENTITY, TARGET_PLAYERS, i);
        if (!entities.getActive(t))
            break;

        bool good = Utils::pointInTriangle(entities.getPosition(t), base_.getPoint(0), base_.getPoint(1), base_.getPoint(2));

        if (good) {
            entities.applyDebuff(currentBeat, t, debuffToApply_, currentBeat + debuffTimer_);
        }
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
    backColor_.setSpeed({ 0.1, 0.1, 0.1, 0.5 });


    Mechanic::reset(beat);
}

std::string Cone::toString()
{
    std::string res;

    res = "CONE," + std::to_string(beat_) + "," + std::to_string(nbShare_) + "," +
       std::to_string(width_) + "," + std::to_string(distance_) + "," + std::to_string(active_) + "," +
        std::to_string(debuffToApply_) + "," + std::to_string(debuffTimer_) + ",";

    res += center_.to_string() + ",";
    res += anchor_.to_string();

    return res;
}

void Cone::getTargetPos(std::vector<sf::Vector2f>& pos)
{
    pos.emplace_back(anchorPos_);
    pos.emplace_back(centerPos_);
}

void Cone::setTargetPos(std::vector<sf::Vector2f>& pos)
{
    if (pos.size() != 2) {
        std::cout << "Cone::setTargetPos : pos vector is wrong size." << std::endl;
        return;
    }

    anchor_.type = TargetType::TARGET_POS;
    anchor_.pos = pos[0];

    center_.type = TargetType::TARGET_POS;
    center_.pos = pos[1];
}

Mechanic* Cone::clone()
{
    return new Cone(*this);
}
