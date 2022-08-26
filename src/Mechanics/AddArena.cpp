#include "AddArena.h"

AddArena::AddArena(float beat, float x, float y, float w, float h)
{
	beat_ = beat;
	passed_ = true;
	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;
}

void AddArena::onPassed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	entities.addArenaPortion(x_, y_, w_, h_);
}

std::string AddArena::toString()
{
	std::string res = "ADDARENA," + std::to_string(beat_) + "," + std::to_string(x_) + "," + std::to_string(y_) 
		+ "," + std::to_string(w_) + "," + std::to_string(h_);

	return res;
}
