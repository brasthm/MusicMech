#include "SnapArena.h"

SnapArena::SnapArena(float beat, float active, const Target& target) : target_(target)
{
	beat_ = beat;
	active_ = active;
}

void SnapArena::onApproach(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	auto pos = entities.getPosition(target_);
	entities.snapArena(pos.x, pos.y);
}

std::string SnapArena::toString()
{
	std::string res = "SNAPARENA," + std::to_string(beat_) + "," + std::to_string(active_)+",";

	res += target_.to_string();

	return res;
}

Mechanic* SnapArena::clone()
{
	return new SnapArena(*this);
}
