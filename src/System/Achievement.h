#ifndef MUSICMECH_CLIENT_ACHIEVEMENT_H
#define MUSICMECH_CLIENT_ACHIEVEMENT_H

#include <string>
#include <vector>
#include <initializer_list>
#include <SFML/Graphics.hpp>

#include "../main.h"

class Achievement {
private:
	std::string name_, desc_;
	std::vector<int> rewardTitles_, rewardBanners_;
	int counter_;
	int max_;
	sf::RenderTexture card_;
	sf::Text nameText_, descText_, rewardText_, progressText_;
public:
	Achievement(std::string name, std::string desc, int max, std::initializer_list<int> rewardTitle, std::initializer_list<int> rewaredBanner);
	const sf::RenderTexture& getAchievmentCard();
};


std::vector<Achievement*>* getAchievementList();


#endif //MUSICMECH_CLIENT_ACHIEVEMENT_H