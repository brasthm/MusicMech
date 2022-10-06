#include "MoveArena.h"

MoveArena::MoveArena(float beat, const Target& target, float speed) : target_(target)
{
    beat_ = beat;
    speed_ = speed;
    passed_ = true;
}

void MoveArena::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    auto pos = entities.getPosition(target_);
    entities.moveArena(pos.x, pos.y, speed_);
}

std::string MoveArena::toString()
{
    std::string res = "MOVEARENA," + std::to_string(beat_) + "," + std::to_string(speed_);

    res += target_.to_string();

    return res;
}

Mechanic* MoveArena::clone()
{
    return new MoveArena(*this);
}
