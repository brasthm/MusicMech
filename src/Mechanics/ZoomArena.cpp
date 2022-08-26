#include "ZoomArena.h"

ZoomArena::ZoomArena(float beat, float val, float speed)
{
    beat_ = beat;
    val_ = val;
    speed_ = speed;
    passed_ = true;
}

void ZoomArena::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    entities.zoomArena(val_, speed_);
}

std::string ZoomArena::toString()
{
    std::string res = "ZOOMARENA," + std::to_string(beat_) + "," + std::to_string(val_)+ "," + std::to_string(speed_);

    return res;
}
