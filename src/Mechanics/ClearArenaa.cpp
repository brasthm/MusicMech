#include "ClearArenaa.h"

ClearArena::ClearArena(float beat)
{
	beat_ = beat;
	passed_ = true;
}

void ClearArena::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	entities.resetArena();
}

std::string ClearArena::toString()
{
	std::string res = "CLEARARENA," + std::to_string(beat_);
	return res;
}
