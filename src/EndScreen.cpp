#include "EndScreen.h"
#include "Graphics/LoadingScreen.h"
#include "System/RessourceLoader.h"
#include "Graphics/ButtonGroup.h"
#include "main.h"

int EndScreen::run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, SongDatabase& songs)
{
	sf::Clock fps;

	LoadingScreen loading;


	SongData song = songs.getSelectedSong();


	sf::Sprite img(RessourceLoader::getTexture(song.image)), vignettebanner(RessourceLoader::getTexture(song.vignette));
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
	finalImage.setColor(sf::Color(0xFFFFFF44));

	if (WIDOW_WIDTH - img.getGlobalBounds().width > WIDOW_HEIGHT - img.getGlobalBounds().height)
		finalImage.setScale(WIDOW_WIDTH / (float)img.getGlobalBounds().width, WIDOW_WIDTH / (float)img.getGlobalBounds().width);
	else if (WIDOW_WIDTH - img.getGlobalBounds().width < WIDOW_HEIGHT - img.getGlobalBounds().height)
		finalImage.setScale(WIDOW_HEIGHT / (float)img.getGlobalBounds().height, WIDOW_HEIGHT / (float)img.getGlobalBounds().height);


	sf::Text headerText;

	headerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	headerText.setString("Clear !");
	headerText.setCharacterSize(108);
	headerText.setPosition(40, 10);
	headerText.setFillColor(sf::Color::Black);

	ButtonGroup buttons;
	buttons.addButton(Button("NEXT", "Next", COLOR_GREEN, 1550, 970, 320, 70));
	buttons.setCurrent(-1);


	vignettebanner.setScale(0.3, 0.3);
	float hpos = 200, height = vignettebanner.getGlobalBounds().height;
	vignettebanner.setPosition(height, hpos);

	sf::RectangleShape header;
	header.setSize({ WIDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(COLOR_GREEN));

	sf::RectangleShape difficultyRect;
	difficultyRect.setSize({ height, height });
	difficultyRect.setFillColor(sf::Color(COLOR_GREEN));
	difficultyRect.setPosition(0, hpos);

	sf::Text artistText, difficultyText;

	artistText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	artistText.setCharacterSize(50);
	artistText.setFillColor(sf::Color::Black);
	artistText.setPosition(height + vignettebanner.getGlobalBounds().width + 10, hpos + 10);

	difficultyText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	difficultyText.setCharacterSize(50);
	difficultyText.setFillColor(sf::Color::Black);

	sf::RectangleShape artistRect;
	artistRect.setFillColor(sf::Color(COLOR_RED));
	artistRect.setPosition(height + vignettebanner.getGlobalBounds().width, hpos);


	artistText.setString(songs.getSelectedSong().artist);
	difficultyText.setString(songs.getSelectedSong().difficulty);
	difficultyText.setPosition(height / 2 - difficultyText.getGlobalBounds().width / 2, hpos + 10);
	artistRect.setSize({ artistText.getGlobalBounds().width + 100, height });

	bool exit = false;
	while (!exit)
	{
		sf::Time elapsedTime = fps.getElapsedTime();
		fps.restart();


		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (!loading.getActive()) {
				if (event.type == sf::Event::Closed)
					return -100;

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1) {
					buttons.setCurrent(-1);
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0) {
					if (buttons.getCurrent() == "NEXT") {
						return 0;
					}
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
					buttons.prev();
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
					buttons.next();
				}
				

			}
		}

		client->keepAlive();

		bg.update(elapsedTime);

		loading.update(elapsedTime);
		buttons.update(elapsedTime);

		window.clear(sf::Color(0x2A2431FF));

		window.draw(finalImage);
		bg.draw(window);
		window.draw(header);
		window.draw(headerText);
		window.draw(vignettebanner);
		window.draw(difficultyRect);
		window.draw(artistRect);

		window.draw(artistText);
		window.draw(difficultyText);


		buttons.draw(window);
		loading.draw(window);
		window.display();
	}

	return 0;
}
