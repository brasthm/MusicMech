#ifndef MUSICMECH_PROFILE_H
#define MUSICMECH_PROFILE_H


#include <SFML/Graphics.hpp>
#include <string>

#include "Achievement.h"


class Profile {
private:
	bool defined_;
	std::string name_;
	char title_id_;
	char banner_id_;
	int id_;
	

	sf::Shader shader_, textShader_;
	sf::Sprite bg_;
	sf::Text nameText_, titleText_;
	sf::Clock clock_;
	sf::RenderTexture card_, returnCard_, textCard_;

	std::vector<Achievement*>* achievementsList_;
public:
	Profile();
	~Profile();
	
	void load(int id);
	void save();

	void create(int id, std::string name);

	bool isDefined();
	std::string getName() const;
	int getBannerId() const;
	int getTitleId() const;

	void setProfile(std::string const& name, int banner, int title);

	const int getNumberAchievement();

	const sf::RenderTexture &getProfileCard();
	const sf::RenderTexture& getAchievementCard(int i);
};


#endif