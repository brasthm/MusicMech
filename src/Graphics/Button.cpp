#include "Button.h"

#include"../System/RessourceLoader.h"


Button::Button(std::string name, std::string text, sf::Uint32 color,float x, float y, float w, float h) : backgound_(x, y, 0, h), name_(name)
{
	x_ = x; y_ = y;
	w_ = w; h_ = h;
	color_ = color;
	backgound_.setFillColor(color_);

	selected_ = false;

	outline_.setPosition(x, y);
	outline_.setSize({ w, h });
	outline_.setOutlineThickness(2);
	outline_.setOutlineColor(sf::Color(color_));
	outline_.setFillColor(sf::Color::Transparent);

	text_.setString(text);
	text_.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	text_.setCharacterSize(50);
	text_.setFillColor(sf::Color::White);
	text_.setPosition(x + w_ / 2 - text_.getGlobalBounds().width / 2, y + 5);
}

void Button::select()
{
	if (!selected_) {
		backgound_.setSize({ w_+1, h_ });
		text_.setFillColor(sf::Color::Black);
		selected_ = true;
	}
}

void Button::unselect()
{
	if (selected_) {
		backgound_.setSize({ 0, h_ });
		text_.setFillColor(sf::Color::White);
		selected_ = false;
	}
}

void Button::update(sf::Time elapsed)
{
	backgound_.update(elapsed);
}

void Button::draw(sf::RenderWindow& window)
{
	backgound_.draw(window);
	window.draw(outline_);
	window.draw(text_);
}

void Button::change(const std::string& name, const std::string& text)
{
	name_ = name;
	text_.setString(text);
}

std::string Button::getName()
{
	return name_;
}
