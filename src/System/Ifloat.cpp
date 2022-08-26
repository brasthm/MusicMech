#include "Ifloat.h"

#include <cmath>
#include <iostream>

IFloat::IFloat(float val)
{
	init(val);
}

void IFloat::init(float val)
{
	prev_ = current_ = target_ = val;
	duration_ = 0;
	moving_ = false;
}

void IFloat::set(float val, float sec)
{
	t_ = sf::seconds(0);
	prev_ = current_;
	target_ = val;
	duration_ = sec;
}

void IFloat::update(sf::Time elapsed)
{
	moving_ = false;
	if (std::abs(target_ - current_) > 1 && t_.asSeconds() < 5*duration_) {
		float diff = target_ - prev_;
		if (std::abs(diff) > 1) {
			t_ += elapsed;
			float a = -std::log(0.01*std::abs(target_ / diff)+0.01) / duration_;
			current_ = diff * (1 - std::exp(-a * t_.asSeconds())) + prev_;
			moving_ = true;
		}
	}
	else {
		current_ = target_;
	}
}

float IFloat::get() {
	return current_;
}

bool IFloat::isMoving() {
	return moving_;
}
