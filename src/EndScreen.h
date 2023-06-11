#ifndef MUSICMECH_CLIENT_END_SCREEN_H
#define MUSICMECH_CLIENT_END_SCREEN_H

#include "System/SongData.h"
#include "Network/Client.h"
#include "Graphics/BackgoundAnimation.h"

#include <SFML/Graphics.hpp>

class EndScreen {

public:
	EndScreen() = default;
	int run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, SongDatabase& songs);
};

#endif