#include "FlexRectangle.h"


FlexRectangle::FlexRectangle(float x, float y, float w, float h) : x_(x), y_(y), w_(w), h_(h) {
	speed_ = 0.5;
}

void FlexRectangle::setPos(sf::Vector2f pos) {
	x_.set(pos.x, speed_);
	y_.set(pos.y, speed_);

}
void FlexRectangle::setSize(sf::Vector2f size) {
	w_.set(size.x, speed_);
	h_.set(size.y, speed_);
}

void FlexRectangle::initPos(sf::Vector2f pos)
{
	x_.init(pos.x);
	y_.init(pos.y);
}

void FlexRectangle::initSize(sf::Vector2f size)
{
	w_.init(size.x);
	h_.init(size.y);
}


sf::Vector2f FlexRectangle::getPos() {
	return rect_.getPosition();
}

sf::Vector2f FlexRectangle::getSize() {
	return rect_.getSize();
}


void FlexRectangle::update(sf::Time elapsed) {
	x_.update(elapsed);
	y_.update(elapsed);
	w_.update(elapsed);
	h_.update(elapsed);

	rect_.setPosition(x_.get(), y_.get());
	rect_.setSize({ w_.get(), h_.get() });
}


void FlexRectangle::update() {
	rect_.setPosition(x_.get(), y_.get());
	rect_.setSize({ w_.get(), h_.get() });
}
void FlexRectangle::draw(sf::RenderWindow &window) {
	window.draw(rect_);
}

void FlexRectangle::draw(sf::RenderTexture &text) {
	rect_.setPosition(0, 0);
	text.draw(rect_);
	update();
}

void FlexRectangle::setFillColor(sf::Uint32 color) {
	rect_.setFillColor(sf::Color(color));
}