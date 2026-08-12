#ifndef MUSICMECH_MENU_ACHIEVEMENT_H
#define MUSICMECH_MENU_ACHIEVEMENT_H


#include <SFML/Graphics.hpp>

#include "Graphics/BackgoundAnimation.h"
#include "Network/Client.h"
#include "System/Profile.h"

class AchievementScreen {
private:

public:
	AchievementScreen();

	int run(sf::RenderWindow& window, BackgroundAnimation& bg, Profile& profiles);
};


#endif