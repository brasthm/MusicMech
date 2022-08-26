#include "RemoveArena.h"


RemoveArena::RemoveArena(float beat, int index)
{
	beat_ = beat;
	index_ = index;
	passed_ = true;
}

void RemoveArena::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	entities.removeArenaPortion(index_);
}

std::string RemoveArena::toString()
{
	std::string res = "REMOVEARENA," + std::to_string(beat_) + "," + std::to_string(index_);
	return res;
}
