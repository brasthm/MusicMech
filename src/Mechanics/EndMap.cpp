#include "EndMap.h"

EndMap::EndMap(float beat)
{
	beat_ = beat;
	passed_ = true;
	Mechanic::setSoundName("Sound/mixkit-notification.wav");
}

void EndMap::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	entities.startEndAnim();
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
