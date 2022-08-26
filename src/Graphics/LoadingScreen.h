#ifndef MUSICMECH_CLIENT_LOADINDSCREEN_H
#define MUSICMECH_CLIENT_LOADINDSCREEN_H

#include <SFML/Graphics.hpp>

#include "ShiftColor.h"
#include "../System/Ifloat.h"

class LoadingScreen {
	sf::RectangleShape fade_;
	sf::Text connectionText_;
	sf::RectangleShape animRect_;
	sf::Clock animClock_;

	ShiftColor color_;

	IFloat angle_;
	int animState_ = 0;

	bool activate_;
	bool finished_ = false;

	sf::Clock clock_;
	
public:
	LoadingScreen();
	void start(std::string text);
	void update(sf::Time elapsedTime);
	void draw(sf::RenderWindow& window);
	bool getActive();
	void stop();
};



#endif