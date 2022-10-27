#include "BeatmapSelection.h"
#include "main.h"
#include "Graphics/Caroussel.h"
#include "Graphics/FlexRectangle.h"
#include "Graphics/ButtonGroup.h"
#include "Graphics/ShiftColor.h"
#include "Graphics/LoadingScreen.h"
#include "Graphics/RingShape.h"
#include "System/RessourceLoader.h"
#include "System/Random.h"

#include <iostream>
#include <future>
#include <thread>

void BeatmapSelection::load(SongDatabase *songs)
{
	for (int i = 0; i < songs->size(); i++) {
		vignettes_.emplace_back(RessourceLoader::getTexture(songs->getSong(i).image));
		vignettes_.back().setScale(350.f / (float)vignettes_.back().getGlobalBounds().height,
			350.f / (float)vignettes_.back().getGlobalBounds().height);
		vignettes_.back().setPosition(900 / 2 - vignettes_.back().getGlobalBounds().width / 2, 180);
	}
}

void BeatmapSelection::run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, SongDatabase* songs, bool* beatmapChanged)
{
	sf::Clock fps;
	bool exit = false;

	sf::Sprite img(RessourceLoader::getTexture(songs->getSelectedSong().image));
	sf::Shader hblur, vblur;

	float radius = 1.5;
	float vradius = radius / img.getGlobalBounds().height;
	float hradius = radius / img.getGlobalBounds().width;

	hblur.loadFromFile(RessourceLoader::getPath("Shader/blur.frag"), sf::Shader::Fragment);
	hblur.setUniform("offsetFactor", sf::Glsl::Vec2(hradius, 0));
	vblur.loadFromFile(RessourceLoader::getPath("Shader/blur.frag"), sf::Shader::Fragment);
	vblur.setUniform("offsetFactor", sf::Glsl::Vec2(0, vradius));

	sf::RenderTexture texture1, texture2;
	texture1.create(img.getGlobalBounds().width, img.getGlobalBounds().height);
	texture1.draw(img, &hblur);
	texture1.display();
	texture2.create(img.getGlobalBounds().width, img.getGlobalBounds().height);
	texture2.draw(sf::Sprite(texture1.getTexture()), &vblur);
	//texture2.draw(img);
	texture2.display();

	sf::Sprite finalImage(texture2.getTexture());
	finalImage.setColor(sf::Color(0xFFFFFF88));


	if (WIDOW_WIDTH - img.getGlobalBounds().width > WIDOW_HEIGHT - img.getGlobalBounds().height)
		finalImage.setScale(WIDOW_WIDTH / (float)img.getGlobalBounds().width, WIDOW_WIDTH / (float)img.getGlobalBounds().width);
	else if (WIDOW_WIDTH - img.getGlobalBounds().width < WIDOW_HEIGHT - img.getGlobalBounds().height)
		finalImage.setScale(WIDOW_HEIGHT / (float)img.getGlobalBounds().height, WIDOW_HEIGHT / (float)img.getGlobalBounds().height);


	Caroussel saucisse(true, 0, 330, 1920, 630, 102, 900, true);
	Caroussel saucisse2(false, 1270, 0, 650, 150, 150, 500);
	FlexRectangle rect(100, 100, 100, 100);

	saucisse.addColor(0xff6392ff);
	saucisse.addColor(0x5ab1bbff);
	saucisse.addColor(0xa5c882ff);
	saucisse.addColor(0xf7dd72ff);

	saucisse2.addColor(0xa5c882ff);
	saucisse2.addColor(0xff6392ff);

	saucisse2.addData("2P", "2 Players");
	saucisse2.addData("4P", "4 Players");


	saucisse.setCharacterSize(70);

	sf::RectangleShape header;
	header.setSize({ WIDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(0x5ab1bbff));

	RingShape placeholder({ 450, 315 }, 30, 5, 0xFFFFFFFF);

	float loading = 0;

	sf::Text headerText;
	headerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	headerText.setString("Room Selection");
	headerText.setCharacterSize(108);
	headerText.setPosition(40, 10);
	headerText.setFillColor(sf::Color::Black);


	for(int i = 0; i < songs->size(); i++)
		saucisse.addData(songs->getSong(i).name, "");
	
	std::cout << "selected " << songs->getSelected() << std::endl;
	saucisse.setCenter(songs->getSelected());
	if(songs->getCurentNbPlayers() == "4")
		saucisse2.right();
	if (songs->getCurentNbPlayers() == "8") {
		saucisse2.right();
		saucisse2.right();
	}
		

	bool changed = false;


	sf::Text titleText, artistText, difficultyText, info, nbPlayers;

	titleText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	titleText.setCharacterSize(52);
	titleText.setFillColor(sf::Color::Black);
	titleText.setPosition(30, 20);

	artistText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	artistText.setCharacterSize(36);
	artistText.setFillColor(sf::Color::Black);
	artistText.setPosition(70, 90);

	difficultyText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	difficultyText.setCharacterSize(36);
	difficultyText.setFillColor(sf::Color::Black);
	difficultyText.setPosition(30, 570);

	nbPlayers.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nbPlayers.setCharacterSize(36);
	nbPlayers.setFillColor(sf::Color::Black);
	nbPlayers.setPosition(30, 530);

	info.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	info.setCharacterSize(32);
	info.setFillColor(sf::Color::White);
	info.setPosition(20, WIDOW_HEIGHT - 42);
	info.setString("W: change mode - Z: random selection");

	std::future<void> loadVignettes = std::async(std::launch::async, &BeatmapSelection::load, this, songs);
	std::future<void> loadSong;

	sf::Clock animRandom;
	bool random = false;
	int nbRandom = 0;

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
				event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1) {
				songs->play();
				exit = true;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
				event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0) {
				songs->setSelected(saucisse.getIndex());
				if (changed && saucisse.isMoving())
					songs->play();
				*beatmapChanged = true;
				return;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
				event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
				event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
				saucisse.left();
				changed = true;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
				event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
				event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
				saucisse.right();
				changed = true;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W ||
				event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 2) {
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X ||
				event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 3) {
				if (!random) {
					random = true;
					nbRandom = Random::randint(20, 50);
				}
			}
		
		}

		if (random && animRandom.getElapsedTime().asSeconds() > 0.03f) {
			animRandom.restart();
			nbRandom--;
			saucisse.left();
			if (nbRandom == 0) {
				random = false;
				changed = true;
			}
				
		}

		if (changed && !saucisse.isMoving()) {
			changed = false;
			int i = saucisse.getIndex();
			
			loadSong = std::async(std::launch::async, &SongDatabase::setSong, songs, i);


			img.setTexture(RessourceLoader::getTexture(songs->getSong(i).image));
			vradius = radius / img.getGlobalBounds().height;
			hradius = radius / img.getGlobalBounds().width;

			texture1.create(img.getGlobalBounds().width, img.getGlobalBounds().height);
			texture1.draw(img, &hblur);
			texture1.display();
			texture2.create(img.getGlobalBounds().width, img.getGlobalBounds().height);
			texture2.draw(sf::Sprite(texture1.getTexture()), &vblur);
			//texture2.draw(img);
			texture2.display();

			finalImage.setTexture(texture2.getTexture());
		}

		bg.update(elapsedTime);
		saucisse.update(elapsedTime);
		//saucisse2.update(elapsedTime);


		titleText.setString(songs->getSong(saucisse.getIndex()).name);
		artistText.setString(songs->getSong(saucisse.getIndex()).artist);
		difficultyText.setString("Difficulty: " + songs->getSong(saucisse.getIndex()).difficulty);
		nbPlayers.setString("Players: " + songs->getSong(saucisse.getIndex()).nbPlayers);

		saucisse.getCenterTexture().draw(titleText);
		saucisse.getCenterTexture().draw(artistText);
		saucisse.getCenterTexture().draw(difficultyText);
		saucisse.getCenterTexture().draw(nbPlayers);
		if (loadVignettes.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
			saucisse.getCenterTexture().draw(vignettes_[saucisse.getIndex()]);
		else {
			loading += 1.3 * elapsedTime.asSeconds();
			if (loading > 1)
				loading -= 1;
			placeholder.setProportion(loading);
			placeholder.draw(saucisse.getCenterTexture());
		}
			


		window.clear(sf::Color(0x2A2431FF));
		window.draw(finalImage);
		bg.draw(window);
		window.draw(header);
		window.draw(headerText);
		saucisse.draw(window);
		//saucisse2.draw(window);
		window.draw(info);
		window.display();
	}

	*beatmapChanged = false;
	return;
}
