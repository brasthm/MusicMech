#ifndef MUSICMECH_CLIENT_FLEXRECTANGLE_H
#define MUSICMECH_CLIENT_FLEXRECTANGLE_H

#include <SFML/Graphics.hpp>
#include "../System/Ifloat.h"



class FlexRectangle {

private:
	sf::RectangleShape rect_;
	float speed_;
	
	IFloat x_, y_, w_, h_;

public:
	FlexRectangle(float x, float y, float w, float h);
	void setPos(sf::Vector2f pos);
	void setSize(sf::Vector2f size);

	sf::Vector2f getPos();
	sf::Vector2f getSize();


	void initPos(sf::Vector2f pos);
	void initSize(sf::Vector2f size);


	void update(sf::Time elapsed);
	void update();
	void draw(sf::RenderWindow &window);
	void draw(sf::RenderTexture &textture);

	void setFillColor(sf::Uint32 color);
};



#endif