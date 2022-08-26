#ifndef MUSICMECH_SERVER_ROOMCREATION_H
#define MUSICMECH_SERVER_ROOMCREATION_H

#include "Graphics/BackgoundAnimation.h"
#include "Network/Client.h"
#include "System/SongData.h"

#include <SFML/Graphics.hpp>

class RoomCreation {
	bool request(Client* client, std::string name, std::string beatmap, std::string mode);

public:
	RoomCreation() = default;
	int run(sf::RenderWindow &window, BackgroundAnimation& bg, Client* client, SongDatabase &songs, std::string &roomName);
};


#endif