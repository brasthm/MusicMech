#include "RotateArena.h"

RotateArena::RotateArena(float beat, float val, float speed)
{
    beat_ = beat;
    val_ = val;
    speed_ = speed;
    passed_ = true;
}

void RotateArena::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    entities.rotateArena(val_, speed_);
}

std::string RotateArena::toString()
{
    std::string res = "ROTATEARENA," + std::to_string(beat_) + "," + std::to_string(val_) + "," + std::to_string(speed_);

    return res;
}
