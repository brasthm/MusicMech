#ifndef MUSICMECH_CLIENT_TEST_SHADDER_H
#define MUSICMECH_CLIENT_TEST_SHADDER_H

#include "Graphics/BackgoundAnimation.h"
#include "Network/Client.h"
#include "System/SongData.h"

#include "Game.h"

#include <SFML/Graphics.hpp>


class TestShadder {

public:
	TestShadder();
	int run(sf::RenderWindow& window, BackgroundAnimation& bg);
};


#endif