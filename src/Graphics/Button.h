#ifndef MUSICMECH_CLIENT_BUTOTN_H
#define MUSICMECH_CLIENT_BUTOTN_H

#include <SFML/Graphics.hpp>
#include "FlexRectangle.h"


class Button {
	FlexRectangle backgound_;
	sf::RectangleShape outline_;
	sf::Text text_;
	sf::Uint32 color_;
	bool selected_, triggerd_;
	std::string name_;
	float x_, y_, w_, h_;


public:
	Button(std::string name, std::string text, sf::Uint32 color, float x, float y, float w, float h);
	void select();
	void unselect();

	void update(sf::Time elapsed);
	void draw(sf::RenderWindow& window);

	void change(const std::string &name, const std::string &text);

	std::string getName();
};


#endif