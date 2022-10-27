#ifndef MUSICMECH_CLIENT_LOBBYSELECTION_H
#define MUSICMECH_CLIENT_LOBBYSELECTION_H


#include "Graphics/BackgoundAnimation.h"
#include "System/SongData.h"
#include "Network/Client.h"
#include <vector>
#include "Game.h"

class LobbySelection {
private:
	bool requestJoinRoom(Client *client, int selection, Game* game);
public:
	LobbySelection();
	~LobbySelection();
	int run(sf::RenderWindow &window, BackgroundAnimation &bg, Client *client, SongDatabase &songs, Game*game);

};

#endif