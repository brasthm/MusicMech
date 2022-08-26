#ifndef MUSICMECH_CLIENT_BUTTONGROUP_H
#define MUSICMECH_CLIENT_BUTTONGROUP_H

#include <vector>
#include "Button.h"


class ButtonGroup {
private:
	std::vector<Button> buttonList_;	
	int current_;

public:
	ButtonGroup();

	void addButton(const Button& button);
	void update(sf::Time elapsed);
	void draw(sf::RenderWindow& window);

	void prev();
	void next();


	void change(int nb, const std::string& name, const std::string& text);

	void setCurrent(int current);
	std::string getCurrent();

};


#endif