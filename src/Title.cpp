#include "Title.h"
#include "main.h"
#include "Graphics/Caroussel.h"
#include "Graphics/FlexRectangle.h"
#include "Graphics/ButtonGroup.h"
#include "Graphics/ShiftColor.h"
#include "Graphics/LoadingScreen.h"
#include "System/RessourceLoader.h"

#include <iostream>
#include <future>



Title::Title()
{
}

int Title::run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client)
{
	sf::Clock fps;
	bool exit = false;


	std::string name = "", server = SERVER_IP.toString();

	FlexRectangle title(0, 480, 1920, 300), moving(0, 0, 0, 0);
	title.setFillColor(COLOR_BLUE);
	moving.setFillColor(COLOR_GREEN);

	sf::Text syncho, beat;

	syncho.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	syncho.setString("Synchro");
	syncho.setCharacterSize(250);
	syncho.setPosition(0, 470);
	syncho.setFillColor(sf::Color::Black);

	beat.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	beat.setString("beat");
	beat.setCharacterSize(250);
	beat.setPosition(syncho.getGlobalBounds().width + 100, 470);
	beat.setFillColor(sf::Color::Black);

	moving.initPos({ syncho.getGlobalBounds().width + 50 ,480 });
	moving.initSize({ beat.getGlobalBounds().width + 150 ,300 });

	sf::Vector2f rectPos(100, 100);

	bool enter = false;
	while (!exit)
	{
		sf::Time elapsedTime = fps.getElapsedTime();
		fps.restart();


		sf::Event event{};
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				exit = true;


			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
				event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 6) {
				exit = true;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
				event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button != 6) {
				exit = true;
				enter = true;
			}

		}

		bg.update(elapsedTime);
		title.update(elapsedTime);
		moving.update(elapsedTime);



		window.clear(sf::Color(0x2A2431FF));
		bg.draw(window);
		title.draw(window);
		moving.draw(window);
		window.draw(syncho);
		window.draw(beat);
		window.display();
	}

	if (!enter) return -1;
	return 0;
}
