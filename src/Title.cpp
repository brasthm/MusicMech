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

bool connect(Client* client, std::string name)
{
	std::cout << "Connecting to server..." << std::endl;


	client->changeName(name);

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

Title::Title()
{
}

int Title::run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client)
{
	sf::Clock fps;
	bool exit = false;
	

	std::string name = "", server = SERVER_IP.toString();

	FlexRectangle title(0, 480, 1920, 300), moving(0, 0, 0, 0);
	title.setFillColor(0x5ab1bbff);
	moving.setFillColor(0xa5c882ff);

	FlexRectangle movingSelector(50, 380, WIDOW_WIDTH * 0.95, 130);
	movingSelector.setFillColor(0xFFFFFF44);

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

	LoadingScreen loading;

	std::future<bool> connected;

	ButtonGroup buttons;
	buttons.addButton(Button("CANCEL", "Cancel", 0xff6392ff, 1250, 970, 250, 70));
	buttons.addButton(Button("CONNECT", "Connect", 0xa5c882ff, 1550, 970, 320, 70));

	int selection = 0;
	int mode = 0;
	int focus = -1;

	sf::Text anameText, aserverText;
	sf::Text nameText, serverText;

	anameText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	anameText.setCharacterSize(40);
	anameText.setFillColor(sf::Color::Black);

	anameText.setString("");

	aserverText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	aserverText.setCharacterSize(40);
	aserverText.setFillColor(sf::Color::Black);
	aserverText.setString(server);

	nameText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nameText.setString("Name");
	nameText.setCharacterSize(70);
	nameText.setPosition(200, 400);
	nameText.setFillColor(sf::Color::Black);

	serverText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	serverText.setString("Server");
	serverText.setCharacterSize(70);
	serverText.setPosition(150, 600);
	serverText.setFillColor(sf::Color::Black);

	sf::RectangleShape cursor;
	cursor.setSize({ 5, 52 });
	cursor.setFillColor(sf::Color::White);

	sf::RectangleShape nameRect, nameFond;
	nameRect.setSize({ nameText.getGlobalBounds().width + 100 , 90 });
	nameRect.setFillColor(sf::Color(0xf7dd72ff));
	nameRect.setPosition(150, 400);

	nameFond.setSize({ WIDOW_WIDTH * 0.6, 60 });
	nameFond.setFillColor(sf::Color(0xf7dd7288));
	nameFond.setPosition(150 + nameText.getGlobalBounds().width + 200, 415);

	sf::RectangleShape serverRect, serverFond;
	serverRect.setSize({ serverText.getGlobalBounds().width + 100 , 90 });
	serverRect.setFillColor(sf::Color(0xff6392ff));
	serverRect.setPosition(100, 600);

	serverFond.setSize({ WIDOW_WIDTH * 0.6, 60 });
	serverFond.setFillColor(sf::Color(0xff639288));
	serverFond.setPosition(100 + serverText.getGlobalBounds().width + 200, 615);


	anameText.setPosition(150 + nameText.getGlobalBounds().width + 220, 420);
	aserverText.setPosition(100 + serverText.getGlobalBounds().width + 220, 620);


	sf::RectangleShape fond;
	fond.setFillColor(sf::Color(0x000000BB));
	fond.setSize({ WIDOW_WIDTH, WIDOW_HEIGHT });
	bool connection = false;

	while (!exit)
	{
		sf::Time elapsedTime = fps.getElapsedTime();
		fps.restart();

		
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (!loading.getActive()) {
				if (event.type == sf::Event::Closed)
					exit = true;


				if (focus == 0 && event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b') {
						if (!name.empty()) name.erase(name.size() - 1, 1);
					}
					else if (event.text.unicode < 127 && event.text.unicode >= 20)
						name += event.text.unicode;
					anameText.setString(name);
				}
				if (focus == 1 && event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b') {
						if (!server.empty()) server.erase(server.size() - 1, 1);
					}
					else if (event.text.unicode < 127 && event.text.unicode >= 20)
						server += event.text.unicode;
					aserverText.setString(server);
				}
				
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 6) {
					if (mode == 1) {
						if (focus != -1) {
							focus = -1;
						}
						else {
							mode = 0;
						}
						
					}
					else if (mode == 0) {
						exit = true;
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button != 6) {
					
					if (mode == 1) {
						if (selection == 0) {
							focus = focus == -1 ? 0 : -1;
						}
						if (selection == 1) {
							focus = focus == -1 ? 1 : -1;
						}
						if (selection == 2) {
							if (buttons.getCurrent() == "CONNECT" && !name.empty() && !server.empty()) {
								SERVER_IP = sf::IpAddress(server);
								connected = std::async(std::launch::async, connect, client, name);
								loading.start("Connecting");
							}
							else if (buttons.getCurrent() == "CANCEL") {
								mode = 0;
							}
						}
					}
					else if (mode == 0) {
						mode = 1;
					}
				}

				if (focus == -1 && mode == 1) {
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
						selection--;
						if (selection < 0) selection = 0;
						else if (selection == 0) {
							movingSelector.setPos({ 50, 380 });
						}
						else if (selection == 1) {
							buttons.setCurrent(-1);
						}
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {
						selection++;
						if (selection > 2) selection = 2;
						else if (selection == 1) {
							movingSelector.setPos({ 50, 580 });
						}
						else if (selection == 2) {
							buttons.setCurrent(1);
						}
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
						if (selection == 2)
							buttons.prev();
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
						if (selection == 2)
							buttons.next();
					}
				}

				
			}
		}

		bg.update(elapsedTime);
		title.update(elapsedTime);
		moving.update(elapsedTime);
		loading.update(elapsedTime);
		movingSelector.update(elapsedTime);
		buttons.update(elapsedTime);


		if (focus == 0) {
			if (name.empty())
				cursor.setPosition(150 + nameText.getGlobalBounds().width + 220 + 5, 420);
			else
				cursor.setPosition(anameText.getGlobalBounds().left + anameText.getGlobalBounds().width + 5, 420);
		}
		if (focus == 1) {
			if (server.empty())
				cursor.setPosition(100 + serverText.getGlobalBounds().width + 220 + 5, 620);
			else
				cursor.setPosition(aserverText.getGlobalBounds().left + aserverText.getGlobalBounds().width + 5, 620);
		}



		if (connected.valid() && connected.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			connection = connected.get();
			if (connection)
				exit = true;
			else
				loading.stop();
		}


		window.clear(sf::Color(0x2A2431FF));
		bg.draw(window);
		title.draw(window);
		moving.draw(window);
		window.draw(syncho);
		window.draw(beat);

		if (mode == 1) {
			window.draw(fond);
			if (selection != 2)
				movingSelector.draw(window);
			window.draw(nameRect);
			window.draw(nameFond);
			window.draw(serverRect);
			window.draw(serverFond);
			window.draw(anameText);
			window.draw(nameText);
			window.draw(serverText);
			window.draw(aserverText);
			buttons.draw(window);
			if (focus != -1)
				window.draw(cursor);
			
		}



		loading.draw(window);
		window.display();
	}
	if (!connection) return -1;
	return 0;
}
