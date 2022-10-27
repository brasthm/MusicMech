#include "TextIndicator.h" 

#include<iostream>
void TextIndicator::updatePosition(EntityManager& entityManager)
{
	sf::Vector2f pos = entityManager.getPosition(target_);
	auto size = displayText_.getGlobalBounds();
	pos_.x = pos.x - size.width / 2;
	pos_.y = pos.y - size.height - 50;
	displayText_.setPosition(pos_);

	drawPriority_ = 150;
}

TextIndicator::TextIndicator(float beat, const Target& target, float duration, std::string text, sf::Uint32 color) : target_(target)
{
	beat_ = beat + duration;
	active_ = duration;
	passed_ = true;

	colorId_ = color;

	text_ = text;
	displayText_.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	displayText_.setString(text_);
	displayText_.setCharacterSize(50);
	displayText_.setOutlineThickness(5);
	displayText_.setFillColor(sf::Color(colorId_));
	displayText_.setOutlineColor(sf::Color::White);
}

void TextIndicator::onDraw(const sf::Time& elapsed, sf::RenderTarget& window)
{
	if (draw_) {
		window.draw(displayText_);
	}
}

void TextIndicator::onApproach(const sf::Time& elapsed, float currentBeat, float cuurentPart, EntityManager& em)
{
	updatePosition(em);
}

void TextIndicator::onFade(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& em)
{
	sf::Color fc = sf::Color(colorId_), oc = sf::Color::White;

	fc.a = 255 * (1 - currentPart);
	oc.a = 255 * (1 - currentPart);

	displayText_.setFillColor(fc);
	displayText_.setOutlineColor(oc);
}

void TextIndicator::reset(float beat)
{
	displayText_.setFillColor(sf::Color(colorId_));
	displayText_.setOutlineColor(sf::Color::White);

	Mechanic::reset(beat);
}

void TextIndicator::getTargetPos(std::vector<sf::Vector2f>& pos)
{
	pos.emplace_back(pos_);
}

void TextIndicator::setTargetPos(std::vector<sf::Vector2f>& pos)
{
	if (pos.size() != 1) {
		std::cout << "Spread::setTargetPos : pos vector is wrong size." << std::endl;
		return;
	}

	target_.type = TargetType::TARGET_POS;
	target_.pos = pos[0];
}

std::string TextIndicator::toString()
{
	std::string res;

	res = "TEXTINDICATOR," + std::to_string(beat_) + "," +
		std::to_string(active_) + "," + std::to_string(colorId_) + "," +
		 text_ + ",";

	res += target_.to_string();

	return res;
}

Mechanic* TextIndicator::clone()
{
	return new TextIndicator(*this);
}
