#include "Arena.h"
#include "../main.h"
#include "Utils.h"

Arena::Arena() : zoom_(100.f), rotation_(0.f), top_(ARENA_WIDTH / 2.f), left_(ARENA_HEIGHT / 2.f), width_(ARENA_WIDTH), height_(ARENA_HEIGHT)
{
	view_.setCenter(sf::Vector2f(ARENA_WIDTH / 2.f, ARENA_HEIGHT / 2.f));
	view_.setSize(sf::Vector2f(WIDOW_WIDTH, WIDOW_HEIGHT));
}

Arena::~Arena()
{

}

void Arena::addRect(float x, float y, float w, float h)
{
	rects_.emplace_back(x, y, w, h);
	borderRects_.emplace_back();
	borderRects_.back().setPosition(x - 5, y - 5);
	borderRects_.back().setSize({ w + 10, h + 10 });
	borderRects_.back().setFillColor(sf::Color::White);
	insideRects_.emplace_back();
	insideRects_.back().setPosition(x, y);
	insideRects_.back().setSize({ w, h});
	insideRects_.back().setFillColor(sf::Color(0x2A2431FF));
}

bool Arena::contains(sf::Vector2f pos)
{
	bool in = false;
	for (auto& rect : rects_) {
		in = in || rect.contains(pos);
	}
	return in;
}

sf::Vector2f Arena::getClosest(sf::Vector2f pos)
{
	std::vector<sf::Vector2f> closest;

	for (auto& rect : rects_) {
		auto r = rect;

		sf::Vector2f closestPoint;

		bool insideX = r.left < pos.x && pos.x < r.left + r.width;
		bool insideY = r.top < pos.y && pos.y < r.top + r.height;
		bool pointInsideRectangle = insideX && insideY;

		if (!pointInsideRectangle) { // Outside
			closestPoint.x = Utils::max(r.left, Utils::min(pos.x, r.left + r.width));
			closestPoint.y = Utils::max(r.top, Utils::min(pos.y, r.top + r.height));
		}
		else { // Inside
			sf::Vector2f distanceToPositiveBounds = sf::Vector2f(r.left + r.width, r.top + r.height) - pos;
			sf::Vector2f distanceToNegativeBounds = -(sf::Vector2f(r.left, r.top) - pos);

			float smallestX = Utils::min(distanceToPositiveBounds.x, distanceToNegativeBounds.x);
			float smallestY = Utils::min(distanceToPositiveBounds.y, distanceToNegativeBounds.y);
			float smallestDistance = Utils::min(smallestX, smallestY);

			if (smallestDistance == distanceToPositiveBounds.x) {
				closestPoint.x = r.left + r.width;
				closestPoint.y = pos.y;
			}
			else if (smallestDistance == distanceToNegativeBounds.x) {
				closestPoint.x = r.left;
				closestPoint.y = pos.y;
			}
			else if (smallestDistance == distanceToPositiveBounds.y) {
				closestPoint.x = pos.x;
				closestPoint.y = r.top + r.height;
			}
			else {
				closestPoint.x = pos.x;
				closestPoint.y = r.top;
			}
		}

		closest.push_back(closestPoint);
	}


	if (closest.size() == 0)
		return pos;

	float closestDistance = Utils::distance(closest[0], pos);
	int index = 0;

	for (int i = 0; i < closest.size(); i++) {
		float c = Utils::distance(closest[i], pos);

		if (c < closestDistance) {
			closestDistance = c;
			index = i;
		}
	}

	return closest[index];
}

void Arena::update(sf::Time elapsed)
{
	zoom_.update(elapsed);
	rotation_.update(elapsed);
	top_.update(elapsed); 
	left_.update(elapsed); 
	width_.update(elapsed); 
	height_.update(elapsed); 
	
	view_.setSize(WIDOW_WIDTH * zoom_.get()/100.f, WIDOW_HEIGHT * zoom_.get()/100.f);
	view_.setRotation(rotation_.get());
	view_.setCenter(left_.get(), top_.get());

}

void Arena::draw(sf::RenderTarget& window)
{
	for (auto& rect : borderRects_) {
		window.draw(rect);
	}

	for (auto& rect : insideRects_) {
		window.draw(rect);
	}
}

void Arena::erase(int i)
{
	rects_.erase(rects_.begin() + i);
	borderRects_.erase(borderRects_.begin() + i);
	insideRects_.erase(insideRects_.begin() + i);
}

void Arena::zoom(float factor, float speed)
{
	zoom_.set(factor, speed);
}

void Arena::rotate(float factor, float speed)
{
	rotation_.set(factor, speed);
}

void Arena::move(float x, float y, float speed)
{
	left_.set(x, speed);
	top_.set(y, speed);
}

void Arena::snap(float x, float y)
{
	left_.init(x);
	top_.init(y);
}

float Arena::getZoom()
{
	return zoom_.get();
}

float Arena::getRotation()
{
	return rotation_.get();
}

float Arena::getTop()
{
	return top_.get();
}

float Arena::getLeft()
{
	return left_.get();
}

float Arena::getWidth()
{
	return width_.get();
}

float Arena::getHeight()
{
	return height_.get();
}

void Arena::setZoom(float factor)
{
	zoom_.init(factor);
}

void Arena::setRotation(float value)
{
	rotation_.init(value);
}

void Arena::setTop(float value)
{
	top_.init(value);
}

void Arena::setLeft(float value)
{
	left_.init(value);
}

void Arena::setWidth(float value)
{
	width_.init(value);
}

void Arena::setHeight(float value)
{
	height_.init(value);
}

int Arena::getNbRects()
{
	return rects_.size();
}

sf::FloatRect Arena::getRects(int i)
{
	return rects_[i];
}

void Arena::clear()
{
	zoom_.init(100.f); 
	rotation_.init(0.f); 
	top_.init((float)ARENA_HEIGHT/2.f);
	left_.init((float)ARENA_WIDTH/2.f);
	width_.init((float)ARENA_WIDTH);
	height_.init((float)ARENA_HEIGHT);
	view_.setCenter(sf::Vector2f(ARENA_WIDTH / 2.f, ARENA_HEIGHT / 2.f));
	view_.setSize(sf::Vector2f(WIDOW_WIDTH, WIDOW_HEIGHT));
	rects_.clear();
	insideRects_.clear();
	borderRects_.clear();
}

sf::View Arena::getView()
{
	return view_;
}

