#include "ButtonGroup.h"

ButtonGroup::ButtonGroup()
{
	current_ = -1;
}

void ButtonGroup::addButton(const Button& button)
{
	buttonList_.emplace_back(button);
}

void ButtonGroup::update(sf::Time elapsed)
{
	for (auto &button : buttonList_)
		button.update(elapsed);
}

void ButtonGroup::draw(sf::RenderWindow& window)
{
	for (auto& button : buttonList_)
		button.draw(window);
}

void ButtonGroup::prev()
{
	if (current_ > 0) {
		buttonList_[current_].unselect();
		current_--;
		buttonList_[current_].select();
	}
	if (current_ == -1) {
		current_ = buttonList_.size() - 1;
		buttonList_[current_].select();
	}
}

void ButtonGroup::next()
{
	if (current_ == -1) {
		current_ = 0;
		buttonList_[current_].select();
	}
	else if (current_ < buttonList_.size() - 1) {
		buttonList_[current_].unselect();
		current_++;
		buttonList_[current_].select();
	}
}

void ButtonGroup::setCurrent(int current)
{
	current_ = current;

	for(int i = 0; i < buttonList_.size(); i++)
		if (current_ == i)
			buttonList_[i].select();
		else
			buttonList_[i].unselect();

		
}

std::string ButtonGroup::getCurrent()
{
	if(current_ == -1)
		return std::string();
	return buttonList_[current_].getName();
}

void ButtonGroup::change(int nb, const std::string& name, const std::string& text)
{
	buttonList_[nb].change(name, text);
}
