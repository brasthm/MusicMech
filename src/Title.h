#ifndef MUSICMECH_CLIENT_TITLE_H
#define MUSICMECH_CLIENT_TITLE_H


#include <SFML/Graphics.hpp>

#include "Graphics/BackgoundAnimation.h"
#include "Network/Client.h"

bool connect(Client* client, std::string name);

class Title {
private:

public:
	Title();

	int run(sf::RenderWindow &window, BackgroundAnimation &bg, Client *client);
};


#endif