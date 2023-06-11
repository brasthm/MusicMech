#include "LoadingScreen.h"

#include "../main.h"
#include "../System/RessourceLoader.h"

LoadingScreen::LoadingScreen() : angle_(45)
{
	fade_.setSize({ WIDOW_WIDTH, WIDOW_WIDTH });
	fade_.setFillColor(sf::Color(0x000000BB));

	connectionText_.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	connectionText_.setString("Connection");
	connectionText_.setCharacterSize(70);
	connectionText_.setPosition(10, WIDOW_HEIGHT - 90);
	connectionText_.setFillColor(sf::Color::White);

	animRect_.setSize({ 40, 40 });
	animRect_.setOrigin(20, 20);
	animRect_.setPosition(connectionText_.getGlobalBounds().width + 80, WIDOW_HEIGHT - 45);

	color_.addTarget("0", COLOR_BLUE);
	color_.addTarget("1", COLOR_GREEN);
	color_.addTarget("2", COLOR_YELLOW);
	color_.addTarget("3", COLOR_RED);
	color_.initCurrent("0");
	color_.setSpeed({ 1, 1, 1, 1 });

	activate_ = false;
	finished_ = false;
}

void LoadingScreen::start(std::string text)
{
	if (!activate_) {
		clock_.restart();
		activate_ = true;
		finished_ = false;
		connectionText_.setString(text);
		animRect_.setPosition(connectionText_.getGlobalBounds().width + 80, WIDOW_HEIGHT - 45);
		angle_.set(angle_.get() + 90, 0.4);
	}
}

void LoadingScreen::update(sf::Time elapsedTime)
{
	if (activate_) {
		if (animClock_.getElapsedTime() > sf::seconds(1)) {
			animClock_.restart();
			animState_++;
			angle_.set(angle_.get() + 90, 0.4);
			color_.setCurrentTarget(std::to_string(animState_ % 4));
		}

		angle_.update(elapsedTime);
		color_.updateColor(elapsedTime);

		animRect_.setRotation(angle_.get());
		animRect_.setFillColor(color_.getCurrentColor());

		if (finished_ && clock_.getElapsedTime().asSeconds() > 0.5f)
			activate_ = false;
	}
}

void LoadingScreen::draw(sf::RenderWindow& window)
{
	if (activate_) {
		window.draw(fade_);
		window.draw(animRect_);
		window.draw(connectionText_);
	}
}

bool LoadingScreen::getActive()
{
	return activate_;
}

void LoadingScreen::stop()
{
	if (clock_.getElapsedTime().asSeconds() > 0.5f)
		activate_ = false;
	else
		finished_ = true;
}
