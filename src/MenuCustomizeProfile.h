#ifndef MUSICMECH_CLIENT_MENU_CUSTOMIZE_PROFILE_H
#define MUSICMECH_CLIENT_MENU_CUSTOMIZE_PROFILE_H

#include "Graphics/BackgoundAnimation.h"
#include "Network/Client.h"
#include "System/SongData.h"

#include "Game.h"

#include <SFML/Graphics.hpp>


class RoomCustomizeProfile {

public:
	RoomCustomizeProfile();
	int run(sf::RenderWindow& window, BackgroundAnimation& bg, Profile &profile);
};


#endif