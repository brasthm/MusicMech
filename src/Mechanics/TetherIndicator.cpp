#include "TetherIndicator.h"
#include "../System/Utils.h"

#include <iostream>

TetherIndicator::TetherIndicator(float beat, const Target& t1, const Target& t2, float duration, sf::Uint32 color) : anchor1_(t1), anchor2_(t2)
{
	beat_ = beat + duration;
	active_ = duration;


    colorId_ = color;
	color_.addTarget("color", colorId_);
	color_.setSpeed({ 0.5, 0.5, 0.5, 0.5 });
	color_.initCurrent("color");

	tether_.setSize({ 100, 4 });
	tether_.setOrigin({ 0, 2 });

	passed_ = true;

    drawPriority_ = 150;
}

void TetherIndicator::onDraw(const sf::Time& elapsed, sf::RenderTarget& window)
{
    if (draw_) {
        tether_.setFillColor(color_.getCurrentColor());
        window.draw(tether_);
    }
}

void TetherIndicator::onApproach(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& em)
{
    color_.updateColor(elapsed);

    pos1_ = em.getPosition(anchor1_);
    pos2_ = em.getPosition(anchor2_);
    auto d = (float)Utils::distance(pos1_, pos2_);

    tether_.setSize({ d, 4 });
    sf::Vector2f dir = (pos2_ - pos1_) / d;
    float signX = pos2_.x - pos1_.x > 0 ? 1 : -1;

    float angle = 0;

    if (signX == 1) {
        tether_.setPosition(pos1_);
        angle = std::atan((float)(pos2_.y - pos1_.y) /
            (float)(pos2_.x - pos1_.x));
    }
    else {
        tether_.setPosition(pos2_);
        angle = std::atan((float)(pos1_.y - pos2_.y) /
            (float)(pos1_.x - pos2_.x));
    }

    angle = 180 * angle / PI;
    tether_.setRotation(angle);
}

void TetherIndicator::onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& em)
{
    color_.setCurrentColor(3, 255 * (1 - currentPart));
}

void TetherIndicator::reset(float beat)
{
    color_.setCurrentColor(3, 255);
    Mechanic::reset(beat);
}

void TetherIndicator::getTargetPos(std::vector<sf::Vector2f>& pos)
{
    pos.emplace_back(pos1_);
    pos.emplace_back(pos2_);
}

void TetherIndicator::setTargetPos(std::vector<sf::Vector2f>& pos)
{
    if (pos.size() != 2) {
        std::cout << "Tether::setTargetPos : pos vector is wrong size." << std::endl;
        return;
    }

    anchor1_.type = TargetType::TARGET_POS;
    anchor1_.pos = pos[0];

    anchor2_.type = TargetType::TARGET_POS;
    anchor2_.pos = pos[1];
}

std::string TetherIndicator::toString()
{
    std::string res;

    res = "TETHERINDICATOR," + std::to_string(beat_) + "," +
        std::to_string(active_) + "," + std::to_string(colorId_) + ",";

    res += anchor1_.to_string() + "," + anchor2_.to_string();

    return res;
}

Mechanic* TetherIndicator::clone()
{
    return new TetherIndicator(*this);
}
