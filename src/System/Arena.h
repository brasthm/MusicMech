#ifndef MUSICMECH_SERVER_ARENA_H
#define MUSICMECH_SERVER_ARENA_H


#include <SFML/Graphics.hpp>

#include "Ifloat.h"

class Arena {
private:
	std::vector<sf::FloatRect> rects_;

	std::vector<sf::RectangleShape> borderRects_, insideRects_;
	sf::View view_;

	sf::RenderTexture renderText_;
	IFloat zoom_, rotation_, top_, left_, width_, height_;
public:
	Arena();

	void addRect(float x, float y, float w, float h);
	bool contains(sf::Vector2f pos);
	sf::Vector2f getClosest(sf::Vector2f pos);

	void update(sf::Time elapsed);
	void draw(sf::RenderWindow& window);
	void erase(int i);

	void zoom(float factor, float speed);
	void rotate(float factor, float speed);
	void move(float x, float y, float speed);
	void snap(float x, float y);

	int getNbRects();
	sf::FloatRect getRects(int i);

	void clear();

	sf::RenderTexture& getRenderTexture();
};


#endif