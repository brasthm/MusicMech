#ifndef MUSICMECH_CLIENT_END_SCREEN_H
#define MUSICMECH_CLIENT_END_SCREEN_H

#include "System/SongData.h"
#include "Network/Client.h"
#include "Graphics/BackgoundAnimation.h"

#include <SFML/Graphics.hpp>

class EndScreen {

public:
	EndScreen() = default;
	void draw_markers(sf::RenderWindow& window, sf::Vector2f position);
	void draw_deaths(sf::RenderWindow& window, Song* song);
	int run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, SongDatabase& songs, Song* currentSong);
};

#endif