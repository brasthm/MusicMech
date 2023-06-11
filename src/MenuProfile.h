#ifndef MUSICMECH_MENU_PROFILE_H
#define MUSICMECH_MENU_PROFILE_H


#include <SFML/Graphics.hpp>

#include "Graphics/BackgoundAnimation.h"
#include "Network/Client.h"
#include "System/Profile.h"

class MenuProfile {
private:

public:
	MenuProfile();

	int run(sf::RenderWindow& window, BackgroundAnimation& bg, std::vector<Profile>& profiles);
};


#endif