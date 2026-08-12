#include "AchievementScreen.h"
#include "Graphics/LoadingScreen.h"
#include "Graphics/FlexRectangle.h"
#include "Graphics/ButtonGroup.h"


AchievementScreen::AchievementScreen()
{
}

int AchievementScreen::run(sf::RenderWindow& window, BackgroundAnimation& bg, Profile& profiles)
{
	sf::Clock fps;
	int exit = 0;

	sf::RectangleShape header;
	header.setSize({ WINDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(COLOR_RED));

	sf::Text headerText;
	headerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	headerText.setString("Achievements");
	headerText.setCharacterSize(108);
	headerText.setPosition(40, 10);
	headerText.setFillColor(sf::Color::Black);

	LoadingScreen loading;

	FlexRectangle movingSelector((WINDOW_WIDTH + 300) / 5 - 360, 150 + (WINDOW_HEIGHT - 150) / 3 - 110, 420, 220);
	movingSelector.setFillColor(0xFFFFFF44);
	bool changed = false;
	int selected = 0;

	int mode = 0;

	std::string name;

	ButtonGroup buttons;
	buttons.addButton(Button("BACK", "Back", COLOR_RED, 1550, 970, 320, 70));
	buttons.setCurrent(0);

	sf::RenderTexture content;
	content.create(WINDOW_WIDTH*0.9, 700);

	float offset = 0;

	while (exit == 0)
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
					exit = -1;
				}


				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button != 6) {
					if (buttons.getCurrent() == "BACK") {
						exit = -1;
					}					
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {

					
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {

					
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {

				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {

				}
			}
		}

		sf::Vector2f vecDep;
		float deadzone = JOYSTICK_DEADZONE / 100;
		float maxzone = JOYSTICK_MAXZONE / 100;
		const std::array<sf::Joystick::Axis, 2> stickX = { sf::Joystick::X, sf::Joystick::U };  // left stick, right stick
		const std::array<sf::Joystick::Axis, 2> stickY = { sf::Joystick::Y, sf::Joystick::V };
		//std::cout << "---" << std::endl;
		for (int gamepad = 0; gamepad < 8; gamepad++)
		{
			if (!sf::Joystick::isConnected(gamepad))
				continue;
			//std::cout << "gamepad " << gamepad << " - x: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::X) << ", y: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::Y) << ", povx: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::PovX) << ", povy: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::PovY) << ", z: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::Z) << ", r: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::R) << ", u: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::U) << ", v: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::V) << std::endl;

			for (size_t stick = 0; stick < stickX.size(); stick++)
			{
				if (!sf::Joystick::hasAxis(gamepad, stickX[stick]) || !sf::Joystick::hasAxis(gamepad, stickY[stick]))
					continue;
				sf::Vector2f stickPos = sf::Vector2f(sf::Joystick::getAxisPosition(gamepad, stickX[stick]) / 100,
					sf::Joystick::getAxisPosition(gamepad, stickY[stick]) / 100);
				vecDep = Utils::remapLength(stickPos, deadzone, maxzone, 0, 1, true);
				//auto p = Utils::remapLength(stickPos, deadzone, maxzone, 0, 1, true);
				//std::cout << "stick " << stick << ": " << p.x << ", " << p.y << std::endl;
			}
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || vecDep.y == -1) {
			offset -= elapsedTime.asSeconds() * 1000;
			if (offset < 0)
				offset = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || vecDep.y == 1) {
			offset += elapsedTime.asSeconds() * 1000;

			if (offset > profiles.getNumberAchievement() * 160 - 700) 
				offset = profiles.getNumberAchievement() * 160 - 700;
		}

		bg.update(elapsedTime);
		movingSelector.update(elapsedTime);
		loading.update(elapsedTime);
		buttons.update(elapsedTime);

		content.clear(sf::Color::Transparent);

		window.clear(sf::Color(0x2A2431FF));
		bg.draw(window);

		window.draw(header);
		window.draw(headerText);
		buttons.draw(window);

		for (int i = 0; i < profiles.getNumberAchievement(); i++) {
			sf::Sprite sp(profiles.getAchievementCard(i).getTexture());
			sp.setPosition(0, 160*i - offset);
			content.draw(sp);
		}

		content.display();

		sf::Sprite sp(content.getTexture());
		sp.setPosition(WINDOW_WIDTH * 0.05, 200);
		window.draw(sp);

		//\movingSelector.draw(window);

		loading.draw(window);
		window.display();
	}

	return exit;
}
