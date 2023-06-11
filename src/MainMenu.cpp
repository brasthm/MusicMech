#include "MainMenu.h"

#include "Graphics/LoadingScreen.h"
#include "Graphics/FlexRectangle.h"

#include <future>
#include "MenuProfile.h"

MainMenu::MainMenu()
{
}

bool connect(Client* client, Profile* profile)
{
	std::cout << "Connecting to server..." << std::endl;


	client->setProfile(*profile);

	bool ok = false;
	if (client->connectToServer()) {
		ok = true;
	}
	

	if (!ok) {
		std::cout << "Unable to connect to server" << std::endl;
		return false;
	}

	std::cout << "Connected to server" << std::endl;
	return true;
}

int MainMenu::run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, Profile& profile)
{
	int exit = 0;
	sf::Clock fps;

	LoadingScreen loading;

	sf::RectangleShape solo;
	solo.setSize({ 700, 435 });
	solo.setFillColor(sf::Color(COLOR_RED));
	solo.setPosition(85, 116);

	sf::Text soloText;
	soloText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	soloText.setString("SOLO MODE");
	soloText.setCharacterSize(90);
	soloText.setPosition(solo.getPosition().x + 10, solo.getPosition().y + solo.getGlobalBounds().height - 100);
	soloText.setFillColor(sf::Color::Black);

	sf::RectangleShape multi;
	multi.setSize({ 950, 924 });
	multi.setFillColor(sf::Color(COLOR_BLUE));
	multi.setPosition(895, 116);

	sf::Text multiText;
	multiText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	multiText.setString("ONLINE CO-OP");
	multiText.setCharacterSize(90);
	multiText.setPosition(multi.getPosition().x + 10, multi.getPosition().y + multi.getGlobalBounds().height - 100);
	multiText.setFillColor(sf::Color::Black);

	sf::RectangleShape achievements;
	achievements.setSize({ 700, 210 });
	achievements.setFillColor(sf::Color(COLOR_YELLOW));
	achievements.setPosition(85, 580);

	sf::Text achievementsText;
	achievementsText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	achievementsText.setString("ACHIEVEMENTS");
	achievementsText.setCharacterSize(78);
	achievementsText.setPosition(achievements.getPosition().x + 10, achievements.getPosition().y + achievements.getGlobalBounds().height - 88);
	achievementsText.setFillColor(sf::Color::Black);

	sf::RectangleShape params;
	params.setSize({ 275, 200 });
	params.setFillColor(sf::Color(COLOR_GREEN));
	params.setPosition(515, 840);

	sf::Text paramsText;
	paramsText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	paramsText.setString("SETTINGS");
	paramsText.setCharacterSize(50);
	paramsText.setPosition(params.getPosition().x + 10, params.getPosition().y + params.getGlobalBounds().height - 60);
	paramsText.setFillColor(sf::Color::Black);

	FlexRectangle movingSelector(solo.getPosition().x - 20, solo.getPosition().y - 20, solo.getGlobalBounds().width + 40, solo.getGlobalBounds().height + 40);
	movingSelector.setFillColor(0xFFFFFF44);

	int cols0 = 0, cols1 = 0, line = 0;
	bool changed = false;
	std::future<bool> connected;
	bool connection = false;

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
					if (cols0 == 0) {
						if (line == 0) {
							exit = 1;
						}
						if (line == 1) {
							exit = 3;
						}
						if (line == 2) {
							if (cols1 == 0) {
								exit = 4;
							}
							if (cols1 == 1) {
								exit = 5;
							}
						}
					}
					if (cols0 == 1) {
						connected = std::async(std::launch::async, connect, client, &profile);
						loading.start("Connecting");
					}
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
					if (cols0 == 0) {
						line--;
						changed = true;
						if (line < 0) {
							line = 0;
							changed = false;
						}
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {
					if (cols0 == 0) {
						line++;
						changed = true;
						if (line > 2) {
							line = 2;
							changed = false;
						}
					}
				}


				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
					if (cols0 == 0) {
						if (line == 2) {
							cols1--;
							changed = true;
							if (cols1 < 0) {
								cols1 = 0;
								changed = false;
							}
						}
					}
					if (cols0 == 1) {
						cols0 = 0;
						changed = true;
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
					if (cols0 == 0) {
						if (line == 2) {
							cols1++;
							if (cols1 == 2) {
								cols1 = 1;
								cols0 = 1;
							}
							changed = true;
						}
						else {
							cols0 = 1;
							changed = true;
						}
					}
					
				}
			}

		}

		sf::Sprite sprite_profile(profile.getProfileCard().getTexture());
		sprite_profile.setPosition(85, 840);

		if (changed) {
			sf::Vector2f position, size;
			sf::FloatRect rect;
			if (cols0 == 0) {
				if (line == 0) {
					position = solo.getPosition();
					rect = solo.getGlobalBounds();
				}
				if (line == 1) {
					position = achievements.getPosition();
					rect = achievements.getGlobalBounds();
				}
				if (line == 2) {
					if (cols1 == 0) {
						position = sprite_profile.getPosition();
						rect = sprite_profile.getGlobalBounds();
					}
					if (cols1 == 1) {
						position = params.getPosition();
						rect = params.getGlobalBounds();
					}
				}
			}
			if (cols0 == 1) {
				position = multi.getPosition();
				rect = multi.getGlobalBounds();
			}

			position.x -= 20;
			position.y -= 20;

			size.x = rect.width + 40;
			size.y = rect.height + 40;

			movingSelector.setPos(position);
			movingSelector.setSize(size);

			changed = false;
		}

		if (connected.valid() && connected.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			connection = connected.get();
			if (connection)
				exit = 2;
			else
				loading.stop();
		}

		bg.update(elapsedTime);
		movingSelector.update(elapsedTime);
		loading.update(elapsedTime);

		window.clear(sf::Color(0x2A2431FF));
		bg.draw(window);		

		window.draw(solo);
		window.draw(multi);
		window.draw(achievements);
		window.draw(sprite_profile);
		window.draw(params);

		window.draw(soloText);
		window.draw(multiText);
		window.draw(achievementsText);
		window.draw(paramsText);

		movingSelector.draw(window);

		loading.draw(window);
		window.display();
	}

	return exit;
}
