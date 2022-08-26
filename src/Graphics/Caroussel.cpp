#include "Caroussel.h"

#include <cmath>
#include <iostream>
Caroussel::Caroussel(bool cycle, float x, float y, float width, float height, float minSize, float maxSize, bool vertical)
{
	x_ = x;
	y_ = y;
	w_ = width;
	h_ = height;
	minSize_ = minSize;
	maxSize_ = maxSize;
	cycle_ = cycle;
	vertical_ = vertical;
	charSize_ = 108;
	toRight_ = false;

	bufferLeft_ = bufferRight_ = 0;


	if (cycle) {
		int nbRect = 1 + std::floor((w_ - maxSize_) / minSize_);
		nbLeft_ = nbRect / 2 - (nbRect % 2 == 0);
		center_ = nbLeft_;
		nbRight_ = nbRect - nbLeft_ - 1;


		for (int i = 0; i < nbLeft_; i++) {
			items_.emplace_back(x_ + i * minSize_, y_, minSize_, h_);
		}
		items_.emplace_back(x_ + nbLeft_ * minSize_, y_, maxSize_, h_);
		items_.back().center = true;
		for (int i = 0; i < nbRight_; i++) {
			items_.emplace_back(x_ + maxSize_ + (nbLeft_ + i) * minSize_, y_, minSize_, h_);
		}
	}
	else {
		nbLeft_ = 0;
		nbRight_ = std::floor((w_ - maxSize_) / minSize_);
		std::cout << nbRight_ << std::endl;
		items_.emplace_back( x_, y_, maxSize_, h_);
		items_.back().center = true;

		for (int i = 0; i < nbRight_; i++) {
			items_.emplace_back(x_ + maxSize_ + i * minSize_, y_, minSize_, h_);
		}
	}	
}


void Caroussel::addData(std::string small, std::string big) {
	data_.emplace_back();
	data_.back().first = small;
	data_.back().second = big;

	if (cycle_) {
		for (int i = 0; i < items_.size(); i++) {			
			if (vertical_) {
				items_[i].small.setRotation(-90);
				items_[i].big.setRotation(-90);
			}
		}
	}
	else {
		for (int i = 0; i < data_.size(); i++) {
			items_[i].small.setString(data_[i].first);
			items_[i].big.setString(data_[i].second);

			if (vertical_) {
				items_[i].small.setRotation(-90);
				items_[i].big.setRotation(-90);
			}
		}
	}
}

void Caroussel::addColor(sf::Uint32 color)
{
	colors_.push_back(color);

	if (cycle_) {
		for (int i = 0; i < items_.size(); i++) {
			int index = i - nbLeft_;

			if (index < 0) index = (colors_.size() - (-index) % colors_.size()) % colors_.size();
			else index = index % colors_.size();
		}
	}
	else {
		for (int i = 0; i < items_.size(); i++) {
			items_[i].rect.setFillColor(colors_[i % colors_.size()]);
		}
	}
	
}

void Caroussel::update(sf::Time elapsed)
{
	for (int i = 0; i < items_.size(); i++) {
		items_[i].rect.update(elapsed);
	}


	for (auto it = items_.begin(); it != items_.end();) {
		if (!toRight_ && bufferLeft_ > 0 && it->rect.getPos().x >= x_ + w_ + 0.1f * minSize_) {
			it = items_.erase(it);
			bufferLeft_--;
		}
		else if (toRight_ && bufferRight_ > 0 && it->rect.getPos().x + 1.1 * minSize_ <= x_) {
			it = items_.erase(it);
			bufferRight_--;
		}
		else
			++it;
	}

	for (int i = 0; i < items_.size(); i++) {
		int indexD = i - center_ - bufferRight_;
		if (indexD < 0) indexD = (data_.size() - (-indexD) % data_.size()) % data_.size();
		else indexD = indexD % data_.size();

		int indexC = i - center_ - bufferRight_;
		if (indexC < 0) indexC = (colors_.size() - (-indexC) % colors_.size()) % colors_.size();
		else indexC = indexC % colors_.size();

		items_[i].small.setString(data_[indexD].first);
		items_[i].big.setString(data_[indexD].second);

		items_[i].rect.setFillColor(colors_[indexC]);
	}

	for (int i = 0; i < items_.size() - 1; i++) {
		items_[i].rect.initSize({ items_[i + 1].rect.getPos().x - items_[i].rect.getPos().x, h_ });
	}
	if(cycle_)
		items_.back().rect.initSize({minSize_, h_ });
	else
		items_.back().rect.initSize({ x_+ w_ - items_.back().rect.getPos().x, h_ });

	for (int i = 0; i < items_.size(); i++) {
		items_[i].rect.update();
	}


	for(int i = 0; i < items_.size(); i++) {
		auto pos = items_[i].rect.getPos();
		auto size = items_[i].rect.getSize();

		if (items_[i].center) {
			auto rect = items_[i].big.getGlobalBounds();
			if (vertical_) {
				items_[i].big.setPosition(size.x / 2 - items_[i].big.getCharacterSize() / 2.f - 10, size.y / 2 + rect.height / 2);
			}
			else {
				items_[i].big.setPosition(size.x / 2 - rect.width / 2, size.y / 2 - items_[i].big.getCharacterSize() / 2.f - 10);
			}

			if (items_[i].rect.getSize().x + 0.5 > 0 && items_[i].rect.getSize().y + 0.5 > 0) {
				centerText_.create(items_[i].rect.getSize().x + 0.5, items_[i].rect.getSize().y + 0.5);
				items_[i].rect.draw(centerText_);
			}

		}
		else {
			auto rect = items_[i].small.getGlobalBounds();
			if (vertical_) {
				if(rect.height < size.y)
					items_[i].small.setPosition(size.x / 2 - items_[i].small.getCharacterSize() / 2.f - 10, size.y / 2 + rect.height / 2);
				else {
					items_[i].shift += 100 * elapsed.asSeconds();
					if (items_[i].shift > rect.height + size.y + 50)
						items_[i].shift = 0;
					items_[i].small.setPosition(size.x / 2 - items_[i].small.getCharacterSize() / 2.f - 10, items_[i].shift);
				}
			}
			else {
				items_[i].small.setPosition(size.x / 2 - rect.width / 2, size.y / 2 - items_[i].small.getCharacterSize() / 2.f - 10);
			}
		}
	}
}

void Caroussel::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < items_.size(); i++) {
		if (items_[i].center == false) {
			sf::RenderTexture text;
			if (items_[i].rect.getSize().x + 0.5 > 0 && items_[i].rect.getSize().y + 0.5 > 0) {
				if (text.create(items_[i].rect.getSize().x + 0.5, items_[i].rect.getSize().y + 0.5)) {
					items_[i].rect.draw(text);
					text.draw(items_[i].center ? items_[i].big : items_[i].small);

					text.display();

					sf::Sprite sprite(text.getTexture());
					sprite.setPosition(items_[i].rect.getPos());
					window.draw(sprite);
				}
			}
		}
		else {
			centerText_.draw(items_[i].center ? items_[i].big : items_[i].small);
			centerText_.display();

			sf::Sprite sprite(centerText_.getTexture());
			sprite.setPosition(items_[i].rect.getPos());
			window.draw(sprite);
		}
	}
}


void Caroussel::left() {
	timer_.restart();
	if (cycle_) {
		int center = nbLeft_ + bufferRight_;
		items_[center].center = false;
		items_[center - 1].center = true;
		for (int i = 0; i < center; i++) {
			items_[i].rect.setPos({ x_ + (i + 1) * minSize_, y_});
		}

		for (int i = center; i < items_.size(); i++) {
			items_[i].rect.setPos({ x_ + maxSize_ + i * minSize_, y_ });
		}
				


		items_.insert(items_.begin(), Item(x_ - minSize_, y_, minSize_, h_));
		items_[0].rect.setPos({x_, y_});


		if (vertical_) {
			items_[0].small.setRotation(-90);
			items_[0].big.setRotation(-90);
		}

		items_[0].small.setCharacterSize(charSize_);
		items_[0].big.setCharacterSize(charSize_);

		center_++;
		bufferLeft_++;

		toRight_ = false;
	}
	else {
		if (nbLeft_ != 0) {
			items_[nbLeft_].rect.setPos({ x_ + maxSize_ + (nbLeft_ - 1) * minSize_, y_ });
			items_[nbLeft_].center = false;
			items_[nbLeft_ - 1].center = true;
			nbLeft_--;
			nbRight_++;
		}
	}
	
}

void Caroussel::right() {
	timer_.restart();
	if (cycle_) {
		int center = nbLeft_ + bufferRight_;
		items_[center].center = false;
		items_[center + 1].center = true;
		for (int i = 0; i <= center +1; i++) {
			items_[i].rect.setPos({ x_ + (i- 1 - bufferRight_) * minSize_, y_ });
		}

		for (int i = center +2; i < items_.size(); i++) {
			items_[i].rect.setPos({ x_ + maxSize_ + (i-2- bufferRight_) * minSize_, y_ });
		}

		float pos = x_ + maxSize_ + (items_.size() - 1 - bufferRight_) * minSize_;
		items_.emplace_back(pos, y_, minSize_, h_);
		items_.back().rect.setPos({ pos - minSize_, y_ });

		if (vertical_) {
			items_.back().small.setRotation(-90);
			items_.back().big.setRotation(-90);
		}

		items_.back().small.setCharacterSize(charSize_);
		items_.back().big.setCharacterSize(charSize_);

		center_--;
		bufferRight_++;

		toRight_ = true;
	}
	else {
		if (nbLeft_ < items_.size() - 1) {
			items_[nbLeft_ + 1].rect.setPos({ x_ + (nbLeft_ + 1) * minSize_, y_ });
			items_[nbLeft_].center = false;
			items_[nbLeft_ + 1].center = true;

			nbLeft_++;
			nbRight_--;
		}
	}
	
}


void Caroussel::setCharacterSize(float val) {
	charSize_ = val;
	for (int i = 0; i < items_.size(); i++) {
		items_[i].small.setCharacterSize(val);
		items_[i].big.setCharacterSize(val);
	}
}

int Caroussel::getIndex()
{
	if (cycle_) {
		int indexD = nbLeft_ - center_;
		if (indexD < 0) indexD = (data_.size() - (-indexD) % data_.size()) % data_.size();
		else indexD = indexD % data_.size();

		return indexD;
	}

	return nbLeft_;
}

std::string Caroussel::getSmallText()
{
	if (cycle_) {
		int indexD = nbLeft_ - center_;
		if (indexD < 0) indexD = (data_.size() - (-indexD) % data_.size()) % data_.size();
		else indexD = indexD % data_.size();

		return data_[indexD].first;
	}
	return items_[nbLeft_].small.getString();
}

std::string Caroussel::getBigText()
{

	if (cycle_) {
		int indexD = nbLeft_ - center_;
		if (indexD < 0) indexD = (data_.size() - (-indexD) % data_.size()) % data_.size();
		else indexD = indexD % data_.size();

		return data_[indexD].second;
	}
	return items_[nbLeft_].big.getString();
}

void Caroussel::setCenter(int center)
{
	center_ -= center;
}

bool Caroussel::isMoving()
{
	return timer_.getElapsedTime().asSeconds() < 0.5;
}

sf::RenderTexture& Caroussel::getCenterTexture()
{
	return centerText_;
}

sf::Vector2f Caroussel::getCenterSize()
{
	return items_[getIndex()].rect.getSize();
}
