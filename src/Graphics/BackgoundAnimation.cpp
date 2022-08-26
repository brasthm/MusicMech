#include "BackgoundAnimation.h"
#include "../main.h"

BackgroundAnimation::BackgroundAnimation() : big_({2000, 400}, 200, 100), small_({ 2000,  250}, 125, 100)
{
	big_.setPosition(-800, 1500);
	big_.setRotation(-45);
	big_.setFillColor(sf::Color(0xFFFFFF55));

	small_.setPosition(1100, 700);
	small_.setRotation(-45);
	small_.setFillColor(sf::Color(0xFFFFFF55));
}

void BackgroundAnimation::update(sf::Time elapsed)
{
	big_.move(8*std::cos(-PI/4.f)*elapsed.asSeconds(), 8*std::sin(-PI / 4.f)*elapsed.asSeconds());
	small_.move(-12 * std::cos(-PI / 4.f)*elapsed.asSeconds(), -12 * std::sin(-PI / 4.f)*elapsed.asSeconds());

	if(big_.getPosition().y < -300) 
		big_.setPosition(-800 - 1000 * std::cos(-PI / 4.f), 1500 - 1000 * std::sin(-PI / 4.f));

	if (small_.getPosition().y > 2800)
		small_.setPosition(1100 + 1000 * std::cos(-PI / 4.f), 700 + 1000 * std::sin(-PI / 4.f));
}

void BackgroundAnimation::draw(sf::RenderWindow & window)
{
	window.draw(big_);
	window.draw(small_);
}
