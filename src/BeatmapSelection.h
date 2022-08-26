#ifndef MUSICMECH_CLIENT_BEATMAPSELECTION_H
#define MUSICMECH_CLIENT_BEATMAPSELECTION_H


#include <SFML/Graphics.hpp>

#include "Graphics/BackgoundAnimation.h"
#include "Network/Client.h"
#include "System/SongData.h"


class BeatmapSelection {
	std::vector<sf::Sprite> vignettes_;
	void load(SongDatabase *songs);
public:
	BeatmapSelection() = default;
	int run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, SongDatabase* songs);
};


#endif