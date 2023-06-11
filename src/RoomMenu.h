#ifndef MUSICMECH_SERVER_ROOMMENU_H
#define MUSICMECH_SERVER_ROOMMENU_H

#include "Graphics/BackgoundAnimation.h"
#include "Network/Client.h"
#include "System/SongData.h"

#include "Game.h"

#include <SFML/Graphics.hpp>


class RoomMenu {
	bool requestReady(Client* client, Game* game, SongDatabase* songs, sf::Uint32 color, bool load);
	bool requestStart(Client* client, Game* game);
public:
	RoomMenu();
	sf::Vector2f getPositionInLayout(int nb, int index);
	int run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, SongDatabase* songs, Game *game, bool creator, bool beatmapChanged);
};


#endif