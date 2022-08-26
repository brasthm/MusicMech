#ifndef MUSICMECH_CLIENT_CAROUSSEL_H
#define MUSICMECH_CLIENT_CAROUSSEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "FlexRectangle.h"
#include "../System/RessourceLoader.h"


class Item {
public:
	FlexRectangle rect;
	sf::Text small, big;
	bool center;
	float shift;

	inline Item(float x, float y, float w, float h) : rect(x, y, w, h) {
		shift = 0;
		small.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
		small.setCharacterSize(108);
		small.setFillColor(sf::Color::Black);

		big.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
		big.setCharacterSize(108);
		big.setFillColor(sf::Color::Black);

		center = false;
	};
};


class Caroussel {
private:
	std::vector<Item> items_;
	std::vector<sf::Uint32> colors_;
	std::vector<std::pair<std::string, std::string>> data_;
	float minSize_, maxSize_;
	float w_, h_;
	float x_, y_;
	int nbLeft_, nbRight_, center_;
	int bufferLeft_, bufferRight_;
	float charSize_;
	bool cycle_, vertical_, toRight_;

	sf::RenderTexture centerText_;

	sf::Clock timer_;

public:
	Caroussel(bool cycle, float x, float y, float width, float height, float minSize, float maxSize, bool vertical=false);
	void addColor(sf::Uint32 color);
	void addData(std::string small, std::string big);
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow &window);
	void left();
	void right();
	void setCharacterSize(float val);
	int getIndex();
	std::string getSmallText();
	std::string getBigText();
	void setCenter(int center);
	bool isMoving();
	sf::RenderTexture& getCenterTexture();
	sf::Vector2f getCenterSize();
	
};



#endif
