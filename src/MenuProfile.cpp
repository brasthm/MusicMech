#include "MenuProfile.h"

#include "Graphics/LoadingScreen.h"
#include "Graphics/FlexRectangle.h"
#include "Graphics/ButtonGroup.h"

MenuProfile::MenuProfile()
{
}

int MenuProfile::run(sf::RenderWindow& window, BackgroundAnimation& bg, std::vector<Profile>& profiles)
{
	sf::Clock fps;
	int exit = -1;

	sf::RectangleShape header;
	header.setSize({ WIDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(COLOR_RED));

	sf::Text headerText;
	headerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	headerText.setString("Profiles");
	headerText.setCharacterSize(108);
	headerText.setPosition(40, 10);
	headerText.setFillColor(sf::Color::Black);

	LoadingScreen loading;

	FlexRectangle movingSelector((WIDOW_WIDTH + 300) / 5 - 360, 150 + (WIDOW_HEIGHT - 150) / 3 - 110, 420, 220);
	movingSelector.setFillColor(0xFFFFFF44);
	bool changed = false;
	int selected = 0;

	int mode = 0;

	std::string name;

	sf::Text anameText;
	sf::Text nameText, errorText;

	anameText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	anameText.setCharacterSize(40);
	anameText.setFillColor(sf::Color::Black);

	errorText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	errorText.setCharacterSize(40);
	errorText.setFillColor(sf::Color::Red);

	anameText.setString("");
	

	nameText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nameText.setString("New profile name");
	nameText.setCharacterSize(70);
	nameText.setPosition(200, 400);
	nameText.setFillColor(sf::Color::Black);

	anameText.setPosition(150 + nameText.getGlobalBounds().width + 220, 420);
	errorText.setPosition(400, 520);

	ButtonGroup buttons;
	buttons.addButton(Button("CANCEL", "Cancel", COLOR_RED, 1250, 970, 250, 70));
	buttons.addButton(Button("CONFIRM", "Confirm", COLOR_GREEN, 1550, 970, 320, 70));
	buttons.setCurrent(1);

	sf::RectangleShape nameRect, nameFond;
	nameRect.setSize({ nameText.getGlobalBounds().width + 100 , 90 });
	nameRect.setFillColor(sf::Color(COLOR_YELLOW));
	nameRect.setPosition(150, 400);

	nameFond.setSize({ WIDOW_WIDTH * 0.4, 60 });
	nameFond.setFillColor(sf::Color(COLOR_SEMI_YELLOW));
	nameFond.setPosition(150 + nameText.getGlobalBounds().width + 200, 415);

	sf::RectangleShape cursor;
	cursor.setSize({ 5, 52 });
	cursor.setFillColor(sf::Color::White);

	sf::RectangleShape fond;
	fond.setFillColor(sf::Color(0x000000BB));
	fond.setSize({ WIDOW_WIDTH, WIDOW_HEIGHT });

	while (exit == -1)
	{
		sf::Time elapsedTime = fps.getElapsedTime();
		fps.restart();

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (!loading.getActive()) {
				if (event.type == sf::Event::Closed)
					exit = -100;

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 6) {
					if (mode == 1) {
						mode = 0;
						name = "";
						anameText.setString(name);
					}
					else
						exit = -2;
				}


				if (mode == 1 && event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b') {
						if (!name.empty()) name.erase(name.size() - 1, 1);
					}
					else if (event.text.unicode < 127 && event.text.unicode >= 20)
						name += event.text.unicode;
					anameText.setString(name);
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button != 6) {
					if (mode == 0) {
						if (profiles[selected].isDefined()) {
							exit = selected;
						}
						else {
							mode = 1;
						}
					}
					else if (mode == 1) {
						if (buttons.getCurrent() == "CONFIRM") {
							if (name.empty()) {
								errorText.setString("Please enter your name");
							}
							else if (name.size() > 10) {
								errorText.setString("Name must be between 1 and 10 characters");
							}
							else {
								profiles[selected].create(selected, name);
								profiles[selected].save();
								exit = selected;
							}
						}
						else if(buttons.getCurrent() == "CANCEL") {
							mode = 0;
							name = "";
							anameText.setString(name);
						}
					}					
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
					if (mode == 0) {
						if (selected >= 4) {
							selected -= 4;
							changed = true;
						}
					}
					
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {
					if (mode == 0) {
						if (selected < 4) {
							selected += 4;
							changed = true;
						}
					}
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
					if (mode == 0) {
						if (selected != 0) {
							selected--;
							changed = true;
						}
					}
					else if (mode == 1) {
						buttons.prev();
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
					if (mode == 0) {
						if (selected != NUMBER_PROFILE - 1) {
							selected++;
							changed = true;
						}
					}
					else if (mode == 1) {
						buttons.next();
					}
				}
			}
		}

		if (changed) {
			
			int ii = selected % 4;
			int jj = selected / 4;
			float x = (WIDOW_WIDTH + 300) / 5 * (ii + 1) - 360;
			float y = 150 + (WIDOW_HEIGHT - 150) / 3 * (jj + 1) - 110;

			movingSelector.setPos(sf::Vector2f(x, y));

			changed = false;
		}

		bg.update(elapsedTime);
		movingSelector.update(elapsedTime);
		loading.update(elapsedTime);
		buttons.update(elapsedTime);

		if (mode == 1) {
			if (name.empty())
				cursor.setPosition(150 + nameText.getGlobalBounds().width + 220 + 5, 420);
			else
				cursor.setPosition(anameText.getGlobalBounds().left + anameText.getGlobalBounds().width + 5, 420);
		}

		window.clear(sf::Color(0x2A2431FF));
		bg.draw(window);

		window.draw(header);
		window.draw(headerText);

		for (int i = 0; i < NUMBER_PROFILE; i++) {
			sf::Sprite sprite_profile(profiles[i].getProfileCard().getTexture());
			int ii = i % 4;
			int jj = i / 4;
			float x = (WIDOW_WIDTH + 300) / 5 * (ii + 1) - 350;
			float y = 150 + (WIDOW_HEIGHT - 150) / 3 * (jj + 1) - 100;
			sprite_profile.setPosition(x, y);
			window.draw(sprite_profile);
		}

		movingSelector.draw(window);


		if (mode == 1) {
			window.draw(fond);
			window.draw(nameRect);
			window.draw(nameFond);
			window.draw(anameText);
			window.draw(nameText);
			buttons.draw(window);
			window.draw(cursor);
			window.draw(errorText);

		}

		loading.draw(window);
		window.display();
	}

	return exit;
}
