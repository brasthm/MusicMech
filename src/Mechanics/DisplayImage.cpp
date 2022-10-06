#include "DisplayImage.h"
#include "../System/RessourceLoader.h"

void DisplayImage::updatePosition(EntityManager& entityManager)
{
	pos_ = entityManager.getPosition(position_);
}

DisplayImage::DisplayImage(float beat, std::string path, float active, const Target& pos): position_(pos)
{
	beat_ = beat;
	active_ = active;
	path_ = path;
	base_.setTexture(RessourceLoader::getTexture(path));
	base_.setColor(sf::Color::Transparent);
	draw_ = false;
	drawPriority_ = 100;
	passed_ = true;
}

void DisplayImage::onDraw(const sf::Time& elapsed, sf::RenderTarget& window)
{
	if (draw_) {
		base_.setPosition(pos_ + shift_);
		base_.setRotation(rotation_);
		window.draw(base_);
	}
}

void DisplayImage::onApproach(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	if (position_.timing == TARGET_FOLLOW) {
		updatePosition(entities);
	}

	if (beat_- currentBeat >= active_ - 1) {
		rotation_ = (1 - currentPart) * 3;

		sf::Color color = sf::Color::White;
		color.a = 255 * currentPart;
		base_.setColor(color);

		shift_.y = 50 * (1 - currentPart);
	}
	else {
		sf::Color color = sf::Color::White;
		color.a = 255;
		base_.setColor(color);
		shift_.y = 0;
		rotation_ = 0;
	}
}

void DisplayImage::onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	sf::Color color = sf::Color::White;
	color.a = 255 * (1 - currentPart);
	base_.setColor(color);
}

void DisplayImage::onInit(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
	if (position_.timing == TARGET_ONINIT) {
		updatePosition(entities);
	}
}

void DisplayImage::reset(float beat)
{
	base_.setColor(sf::Color::White);
}

std::string DisplayImage::toString()
{
	std::string res;

	res = "DISPLAYIMAGE," + std::to_string(beat_) + "," + path_ + "," +  std::to_string(active_) + ",";

	res += position_.to_string();

	return res;
}

Mechanic* DisplayImage::clone()
{
	return new DisplayImage(*this);
}
