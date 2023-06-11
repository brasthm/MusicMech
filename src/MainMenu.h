#ifndef MUSICMECH_MAIN_TITLE_H
#define MUSICMECH_MAIN_TITLE_H


#include <SFML/Graphics.hpp>

#include "Graphics/BackgoundAnimation.h"
#include "Network/Client.h"
#include "System/Profile.h"

bool connect(Client* client, Profile *name);

class MainMenu {
private:

public:
	MainMenu();

	int run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, Profile &profile);
};


#endif