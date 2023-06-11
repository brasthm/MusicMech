#include "EndMap.h"

EndMap::EndMap(float beat)
{
	beat_ = beat;
	Mechanic::setSoundName("Sound/mixkit-notification.wav");
}

void EndMap::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	entities.startEndAnim();
}

void EndMap::onCheck(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	passed_ = true;
}

std::string EndMap::toString()
{
	std::string res;

	res = "ENDMAP," + std::to_string(beat_);

	return res;
}

Mechanic* EndMap::clone()
{
	return new EndMap(*this);
}
