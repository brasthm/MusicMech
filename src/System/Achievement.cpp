#include "Achievement.h"
#include "../STRINGS.h"
#include "RessourceLoader.h"

Achievement::Achievement(std::string name, std::string desc, int max, std::initializer_list<int> rewardTitle, std::initializer_list<int> rewaredBanner) :
	name_(name), desc_(desc), max_(max), rewardBanners_{ rewaredBanner }, rewardTitles_{ rewardTitle }
{
	counter_ = 0;
	card_.create(WINDOW_WIDTH * 0.9, 150);

	nameText_.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nameText_.setFillColor(sf::Color::Black);
	nameText_.setCharacterSize(40);
	nameText_.setPosition(10, 0);

	descText_.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	descText_.setFillColor(sf::Color::Black);
	descText_.setCharacterSize(30);
	descText_.setPosition(50, 45);

	rewardText_.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	rewardText_.setFillColor(sf::Color::Black);
	rewardText_.setCharacterSize(15);
	rewardText_.setPosition(50, 125);

	progressText_.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	progressText_.setFillColor(sf::Color::Black);
	progressText_.setCharacterSize(25);
	

}

const sf::RenderTexture& Achievement::getAchievmentCard()
{
	nameText_.setString(name_);
	descText_.setString(desc_);
	progressText_.setString(std::to_string(counter_) + "/" + std::to_string(max_));
	std::string res = "Reward: ";

	int nbTot = rewardTitles_.size() + rewardBanners_.size();

	for (int i = 0; i < rewardTitles_.size(); i++) {
		res += TITLES[rewardTitles_[i]] + " <Title>";

		if (i < nbTot - 1)
			res += ", ";
	}
		
	for (int i = 0; i < rewardBanners_.size(); i++) {
		res += BANNERS[rewardBanners_[i]].name + " <Banner>";

		if (rewardTitles_.size() + i < nbTot - 1)
			res += ", ";
	}

	sf::RectangleShape background, fillBackground;
	background.setSize(sf::Vector2f(WINDOW_WIDTH * 0.8, 30));
	background.setPosition(WINDOW_WIDTH * 0.05, 85);
	background.setFillColor(sf::Color(COLOR_RED));


	fillBackground.setSize(sf::Vector2f(WINDOW_WIDTH * 0.8 * (float)counter_/(float)max_, 30));
	fillBackground.setPosition(WINDOW_WIDTH * 0.05, 85);
	fillBackground.setFillColor(sf::Color(COLOR_GREEN));

	progressText_.setPosition(WINDOW_WIDTH * 0.05 + WINDOW_WIDTH * 0.8 / 2 - progressText_.getGlobalBounds().width / 2, 85);


		
	rewardText_.setString(res);

	card_.clear(sf::Color(COLOR_YELLOW));
	card_.draw(nameText_);
	card_.draw(descText_);
	card_.draw(rewardText_);
	card_.draw(background);
	card_.draw(fillBackground);
	card_.draw(progressText_);

	card_.display();

	return card_;
}

std::vector<Achievement*>* getAchievementList()
{
	std::vector<Achievement*>* achievements = new std::vector<Achievement*>;

	//achievements->emplace_back(new Achievement("That's a clear! III", "Clear 5 songs", 5, {}, {}));

	achievements->emplace_back(new Achievement("Now go play with your friends", "Clear all songs in Solo Mode", 1, { TITLE_EAGER }, {}));

	achievements->emplace_back(new Achievement("That's a clear! I", "Clear 1 song", 1, { TITLE_NOVICE }, {}));
	achievements->emplace_back(new Achievement("That's a clear! II", "Clear 5 songs", 5, {}, { BANNER_BLUE, BANNER_GREEN, BANNER_RED, BANNER_YELLOW }));
	achievements->emplace_back(new Achievement("That's a clear! III", "Clear 10 songs", 10, { TITLE_CLEARER }, {}));

	achievements->emplace_back(new Achievement("Perfect! I", "Clear 1 song without retrying", 1, { TITLE_ONESHOT }, {}));
	achievements->emplace_back(new Achievement("Perfect! II", "Clear 5 songs without retrying", 5, {}, { BANNER_BLUE_RAINBOW, BANNER_GREEN_RAINBOW, BANNER_RED_RAINBOW, BANNER_YELLOW_RAINBOW }));
	achievements->emplace_back(new Achievement("Perfect! III", "Clear 10 songs without retrying", 10, { TITLE_FLAWLESS }, {}));

	achievements->emplace_back(new Achievement("Elusive I", "Clear 1 song without getting hit", 1, { TITLE_INVINCIBLE }, {}));
	achievements->emplace_back(new Achievement("Elusive II", "Clear 5 songs without getting hit", 5, {}, { BANNER_BLUE_BRILLANT, BANNER_GREEN_BRILLANT, BANNER_RED_BRILLANT, BANNER_YELLOW_BRILLANT }));
	achievements->emplace_back(new Achievement("Elusive III", "Clear 10 songs without getting hit", 10, { TITLE_UNBREAKABLE }, {}));

	achievements->emplace_back(new Achievement("I panicked", "Fail 1 time", 1, { TITLE_PANICKED }, {}));
	achievements->emplace_back(new Achievement("It's the controller's fault", "Fail 50 times", 50, { TITLE_CONTROLLER }, {}));
	achievements->emplace_back(new Achievement("I'm not early, I anticipate", "Fail 100 times", 100, { TITLE_EARLY }, {}));
	achievements->emplace_back(new Achievement("I blame this on yellow", "Fail 250 times", 250, { TITLE_YELLOW }, {}));
	achievements->emplace_back(new Achievement("It's lag", "Fail 500 times", 500, { TITLE_LAG }, {}));


	for (int i = 0; i < ALL_TRACKED_STATS.size(); i++) {
		achievements->emplace_back(new Achievement(getTitleByStatistic(i, true), "Be " + getDescriptionByStatistic(i, true), 1, { TITLE_GOTTAGOFAR + 2 * i }, {}));
		achievements->emplace_back(new Achievement(getTitleByStatistic(i, false), "Be " + getDescriptionByStatistic(i, false), 1, { TITLE_GOTTAGOFAR + 2 * i + 1 }, {}));
	}

	return achievements;
}
