#ifndef MUSICMECH_CLIENT_BACKGROUNDANIMATION_H
#define MUSICMECH_CLIENT_BACKGROUNDANIMATION_H

#include "RoundedRectangle.h"
#include <SFML/Graphics.hpp>


class BackgroundAnimation {
private:
	sf::RoundedRectangleShape big_, small_;


public:
	BackgroundAnimation();
	
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow &window);
};



#endif