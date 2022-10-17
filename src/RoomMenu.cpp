#include "RoomMenu.h"

#include "Graphics/LoadingScreen.h"
#include "System/RessourceLoader.h"
#include "Graphics/ButtonGroup.h"

#include <future>

bool RoomMenu::requestReady(Client* client, Game* game, SongDatabase* songs, sf::Uint32 color, bool load)
{
	if(load)
		game->load(songs->getSelectedPath());
	bool ok = client->sendReady(color);
	return ok;
}

bool RoomMenu::requestStart(Client* client, Game* game)
{
	bool ok = client->requestLaunchGame();
	return ok;
}

RoomMenu::RoomMenu()
{
}

int RoomMenu::run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, SongDatabase* songs, Game* game, bool creator, bool beatmapChanged)
{
	sf::Clock fps;
	bool exit = false, focus = false, first = true;

	int selection = 0;

	LoadingScreen loading;

	SongData song = songs->getSelectedSong();
	if (!songs->isPlaying())
		songs->play();

	sf::Sprite img(RessourceLoader::getTexture(song.image));
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
	headerText.setString("Room - " + client->getCurrentLobby().name);
	headerText.setCharacterSize(108);
	headerText.setPosition(40, 10);
	headerText.setFillColor(sf::Color::Black);

	ButtonGroup buttons;
	if (creator) {
		buttons.addButton(Button("BACK", "Back", 0xff6392ff, 100, 970, 250, 70));
		buttons.addButton(Button("COLOR", "Choose Color", 0xf7dd72ff, 400, 970, 350, 70));
		buttons.addButton(Button("BEATMAP", "Change Beatmap", 0x5ab1bbff, 800, 970, 400, 70));
		buttons.addButton(Button("READY", "Ready", 0xf7dd72ff, 1250, 970, 250, 70));
		buttons.addButton(Button("START", "Start", 0xa5c882ff, 1550, 970, 320, 70));
		buttons.setCurrent(3);
	}
	else {
		
		buttons.addButton(Button("BACK", "Back", 0xff6392ff, 850, 970, 250, 70));
		buttons.addButton(Button("COLOR", "Choose Color", 0xf7dd72ff, 1150, 970, 350, 70));
		buttons.addButton(Button("READY", "Ready", 0xa5c882ff, 1550, 970, 320, 70));
		buttons.setCurrent(2);
	}

	


	sf::RectangleShape header;
	header.setSize({ WIDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(0xf7dd72ff));

	sf::RectangleShape playerRect;
	playerRect.setSize({ WIDOW_WIDTH * 0.5, 100 });
	playerRect.setFillColor(sf::Color(0xff6392ff));
	playerRect.setPosition(0, 230);

	sf::RectangleShape beatmapRect;
	beatmapRect.setSize({ WIDOW_WIDTH * 0.5, 630 });
	beatmapRect.setFillColor(sf::Color(0xa5c882ff));
	beatmapRect.setPosition(WIDOW_WIDTH * 0.5, 230);


	sf::Text playerText;
	playerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	playerText.setString("Players");
	playerText.setCharacterSize(70);
	playerText.setPosition(20, 240);
	playerText.setFillColor(sf::Color::Black);

	sf::Text titleText, artistText, difficultyText;

	titleText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	titleText.setCharacterSize(52);
	titleText.setFillColor(sf::Color::Black);
	titleText.setPosition(WIDOW_WIDTH * 0.5 + 30, 230 + 20);
	

	artistText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	artistText.setCharacterSize(36);
	artistText.setFillColor(sf::Color::Black);
	artistText.setPosition(WIDOW_WIDTH * 0.5 + 70, 230 + 90);

	difficultyText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	difficultyText.setCharacterSize(36);
	difficultyText.setFillColor(sf::Color::Black);
	difficultyText.setPosition(WIDOW_WIDTH * 0.5 + 30, 230 + 570);

	sf::Sprite vignette;

	vignette.setTexture(RessourceLoader::getTexture(songs->getSelectedSong().image));
	vignette.setScale(350.f / (float)vignette.getGlobalBounds().height,
		350.f / (float)vignette.getGlobalBounds().height);
	vignette.setPosition(WIDOW_WIDTH * 0.5 + WIDOW_WIDTH * 0.5 / 2 - vignette.getGlobalBounds().width / 2, 230 + 180);

	std::vector<sf::RectangleShape> playersRect;
	std::vector<sf::Text> playersText;

	int nbMax = client->getCurrentLobby().limit;

	std::vector<bool> ready(nbMax);

	for (int i = 0; i < 4; i++) {
		playersRect.emplace_back();
		playersText.emplace_back();
		playersRect.back().setSize({ WIDOW_WIDTH * 0.5, 60 });
		playersRect.back().setFillColor(sf::Color(i % 2 == 0 ? 0xf7dd72ff : 0x5ab1bbff));
		playersRect.back().setPosition(0, 330 + 60 * i);
		playersText.back().setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
		playersText.back().setCharacterSize(40);
		playersText.back().setPosition(70, 340 + 60 * i);
		playersText.back().setFillColor(sf::Color::Black);
	}

	std::vector<sf::Uint32> colors;

	colors.emplace_back(0x3B00EAFF);
	colors.emplace_back(0xAAFF1FFF);
	colors.emplace_back(0xFF007DFF);
	colors.emplace_back(0xFFF100FF);

	std::vector<sf::CircleShape> circles;


	circles.emplace_back(20.f, 500);
	circles.emplace_back(20.f, 500);
	circles.emplace_back(20.f, 500);
	circles.emplace_back(20.f, 500);

	for (int i = 0; i < circles.size(); i++) {
		circles[i].setOutlineThickness(3);
		circles[i].setOutlineColor(sf::Color::Black);
		circles[i].setFillColor(sf::Color::Black);
		circles[i].setPosition(WIDOW_WIDTH * 0.5 - 100, 340 + 60 * i);
	}


	sf::CircleShape rightArrow(20.f, 3);
	rightArrow.setOrigin(20, 20);
	rightArrow.setRotation(90);
	rightArrow.setOutlineColor(sf::Color::Black);
	rightArrow.setOutlineThickness(3);
	rightArrow.setPosition(WIDOW_WIDTH * 0.5 - 50 + 20, 20 + 340 + 60 * client->getPlayerIndex());

	sf::CircleShape leftArrow(20.f, 3);
	leftArrow.setOrigin(20, 20);
	leftArrow.setRotation(-90);
	leftArrow.setOutlineColor(sf::Color::Black);
	leftArrow.setOutlineThickness(3);
	leftArrow.setPosition(WIDOW_WIDTH * 0.5 - 150 + 20, 20 + 340 + 60 * client->getPlayerIndex());

	titleText.setString(songs->getSelectedSong().name);
	artistText.setString(songs->getSelectedSong().artist);
	difficultyText.setString("Difficulty: " + songs->getSelectedSong().difficulty);

	sf::Sprite check(RessourceLoader::getTexture("Images/check.png"));

	std::future<bool> disconnect, refresh, beatmap, setReady, launchGame, waiting;

	int state = 0;

	int playerIndex = client->getPlayerIndex();
	int selectedColorIndex = playerIndex, prevColorIndex = selectedColorIndex;
	sf::Uint32 selectedColor = colors[playerIndex];
	circles[playerIndex].setFillColor(sf::Color(selectedColor));


	for (int i = 0; i < nbMax; i++) {
		playersText[i].setString(client->getCurrentLobby().players[i]->name);
		ready[i] = client->getCurrentLobby().players[i]->status == PlayerStatus::PLAYER_READY;
		if (ready[i])
			circles[i].setFillColor(sf::Color(client->getCurrentLobby().players[i]->color));
	}

	int saveColor;

	if (creator && beatmapChanged) 
		beatmap = std::async(std::launch::async, &Client::requestBeatmapChange, client, songs->getSelectedSong().id, songs->getMode());
	else 
		refresh = std::async(std::launch::async, &Client::requestLobbyInfo, client, client->getLobbyIndex());
	

	loading.start("Loading room");
	

	while (!exit)
	{
		sf::Time elapsedTime = fps.getElapsedTime();
		fps.restart();

		
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (!loading.getActive()) {
				if (event.type == sf::Event::Closed)
					return -1;

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1) {
					if (selection == 0) {
						if (!ready[playerIndex]) {
							disconnect = std::async(std::launch::async, &Client::requestLobbyDisconnect, client);
							loading.start("Disconnecting");
						}
						else {
							saveColor = colors[selectedColorIndex];
							setReady = std::async(std::launch::async, &RoomMenu::requestReady, this, client, game, songs, 0, false);
							loading.start("Loading");

							if (creator)
								buttons.change(3, "READY", "Ready");
							else
								buttons.change(2, "READY", "Ready");
						}
					}
					else if (selection == 1) {
						selection = 0;
						buttons.setCurrent(1);
						selectedColorIndex = prevColorIndex;
						circles[playerIndex].setFillColor(sf::Color(colors[selectedColorIndex]));
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0) {
					if (selection == 0) {
						if (buttons.getCurrent() == "BACK") {
							disconnect = std::async(std::launch::async, &Client::requestLobbyDisconnect, client);
							loading.start("Disconnecting");
						}
						else if (buttons.getCurrent() == "COLOR") {
							if (!ready[playerIndex]) {
								selection = 1;
								buttons.setCurrent(-1);
							}
						}
						else if (buttons.getCurrent() == "BEATMAP") {
							if (!ready[playerIndex]) {
								return 1;
							}
						}
						else if (buttons.getCurrent() == "READY") {
							saveColor = colors[selectedColorIndex];
							setReady = std::async(std::launch::async, &RoomMenu::requestReady, this, client, game, songs, saveColor, true);
							loading.start("Loading");

							if(creator)
								buttons.change(3, "NOTREADY", "Stop");
							else 
								buttons.change(2, "NOTREADY", "Stop");
						}
						else if (buttons.getCurrent() == "NOTREADY") {
							saveColor = colors[selectedColorIndex];
							setReady = std::async(std::launch::async, &RoomMenu::requestReady, this, client, game, songs, 0, false);
							loading.start("Loading");

							if (creator)
								buttons.change(3, "READY", "Ready");
							else
								buttons.change(2, "READY", "Ready");
						}
						else if (buttons.getCurrent() == "START") {
							bool ok = true;
							for (int i = 0; i < nbMax; i++)
								ok = ok && ready[i];
							ok = ready[0];
							if (ok) {
								launchGame = std::async(std::launch::async, &RoomMenu::requestStart, this, client, game);
								loading.start("Launching");
							}
						}
					}
					else if (selection == 1) {
						selection = 0;
						buttons.setCurrent(1);
						selectedColor = colors[selectedColorIndex];
						prevColorIndex = selectedColorIndex;
					}
						

				}
				if (!focus) {
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
						if (selection == 0)
							buttons.prev();
						else {
							selectedColorIndex--;
							if (selectedColorIndex < 0)
								selectedColorIndex = colors.size() - 1;
							circles[playerIndex].setFillColor(sf::Color(colors[selectedColorIndex]));
						}
					}
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
						if (selection == 0)
							buttons.next();
						else {
							selectedColorIndex++;
							if (selectedColorIndex >= colors.size())
								selectedColorIndex = 0;
							circles[playerIndex].setFillColor(sf::Color(colors[selectedColorIndex]));
						}
					}
				}

			}
		}

		if (disconnect.valid() && disconnect.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			songs->stop();
			loading.stop();
			return -1;
		}

		if (refresh.valid() && refresh.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			std::cout << "Room refresh request" << std::endl;
			nbMax = client->getCurrentLobby().limit;
			songs->setMode(client->getCurrentLobby().mode);
			if (songs->getSelectedSong().id != client->getCurrentLobby().beatmap) {
				songs->setSelectedById(client->getCurrentLobby().beatmap);
				titleText.setString(songs->getSelectedSong().name);
				artistText.setString(songs->getSelectedSong().artist);
				difficultyText.setString("Difficulty: " + songs->getSelectedSong().difficulty);

				vignette = sf::Sprite(RessourceLoader::getTexture(songs->getSelectedSong().image));
				vignette.setScale(350.f / (float)vignette.getGlobalBounds().height,
					350.f / (float)vignette.getGlobalBounds().height);
				vignette.setPosition(WIDOW_WIDTH * 0.5 + WIDOW_WIDTH * 0.5 / 2 - vignette.getGlobalBounds().width / 2, 230 + 180);


				img = sf::Sprite(RessourceLoader::getTexture(songs->getSelectedSong().image));
				vradius = radius / img.getGlobalBounds().height;
				hradius = radius / img.getGlobalBounds().width;

				hblur.loadFromFile(RessourceLoader::getPath("Shader/blur.frag"), sf::Shader::Fragment);
				hblur.setUniform("offsetFactor", sf::Glsl::Vec2(hradius, 0));
				vblur.loadFromFile(RessourceLoader::getPath("Shader/blur.frag"), sf::Shader::Fragment);
				vblur.setUniform("offsetFactor", sf::Glsl::Vec2(0, vradius));

				texture1.create(img.getGlobalBounds().width, img.getGlobalBounds().height);
				texture1.draw(img, &hblur);
				texture1.display();
				texture2.create(img.getGlobalBounds().width, img.getGlobalBounds().height);
				texture2.draw(sf::Sprite(texture1.getTexture()), &vblur);
				texture2.display();

				finalImage = sf::Sprite(texture2.getTexture());
				finalImage.setColor(sf::Color(0xFFFFFF44));


				if (WIDOW_WIDTH - img.getGlobalBounds().width > WIDOW_HEIGHT - img.getGlobalBounds().height)
					finalImage.setScale(WIDOW_WIDTH / (float)img.getGlobalBounds().width, WIDOW_WIDTH / (float)img.getGlobalBounds().width);
				else if (WIDOW_WIDTH - img.getGlobalBounds().width < WIDOW_HEIGHT - img.getGlobalBounds().height)
					finalImage.setScale(WIDOW_HEIGHT / (float)img.getGlobalBounds().height, WIDOW_HEIGHT / (float)img.getGlobalBounds().height);

				songs->play();
			}

			for (int i = 0; i < nbMax; i++) {
				playersText[i].setString(client->getCurrentLobby().players[i]->name);
				ready[i] = client->getCurrentLobby().players[i]->status == PlayerStatus::PLAYER_READY;
				if (ready[i])
					circles[i].setFillColor(sf::Color(client->getCurrentLobby().players[i]->color));
				if (i == playerIndex) {
					if (!ready[i]) {
						if (creator)
							buttons.change(3, "READY", "Ready");
						else
							buttons.change(2, "READY", "Ready");
					}
					else {
						if (creator)
							buttons.change(3, "NOTREADY", "Stop");
						else
							buttons.change(2, "NOTREADY", "Stop");
					}

				}
			}

			refresh = std::future<bool>();
			loading.stop();
		}

		if (beatmap.valid() && beatmap.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			beatmap = std::future<bool>();
			loading.stop();
		}

		if (setReady.valid() && setReady.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			setReady = std::future<bool>();
			loading.stop();
		}


		if (launchGame.valid() && launchGame.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {

			launchGame = std::future<bool>();
		}

		if (waiting.valid() && waiting.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			std::cout << "bleep" << std::endl;
			if (waiting.get()) {
				std::cout << "blop" << std::endl;
				loading.stop();
				songs->stop();
				return 2;
			}

			std::cout << "bloop" << std::endl;

			waiting = std::future<bool>();
			loading.stop();
		}

		

		state = 0;
		if(!disconnect.valid() && !refresh.valid() && !beatmap.valid() && !setReady.valid() && !launchGame.valid() && !waiting.valid())
			client->monitorLobby(state);

		if (state == -1) {
			disconnect = std::async(std::launch::async, &Client::requestLobbyDisconnect, client);
			loading.start("Disconnecting");
		}
		if (state == 1) {
			loading.start("Loading");
			waiting = std::async(std::launch::async, &Client::waitToStart, client);

			game->clearPlayer();
			for (int i = 0; i < NB_MAX_JOUEURS; i++) {
				game->addPlayer(client->getCurrentLobby().players[i]->name, client->getCurrentLobby().players[i]->color);
			}
		}
			
		if (state == 2) {
			refresh = std::async(std::launch::async, &Client::requestLobbyInfo, client, client->getLobbyIndex());
		}

		bg.update(elapsedTime);

		loading.update(elapsedTime);
		buttons.update(elapsedTime);

		window.clear(sf::Color(0x2A2431FF));

		window.draw(finalImage);
		bg.draw(window);
		window.draw(header);
		window.draw(headerText);
		window.draw(playerRect);
		window.draw(playerText);
		window.draw(beatmapRect);

		window.draw(titleText);
		window.draw(artistText);
		window.draw(difficultyText);
		window.draw(vignette);

		

		for (int i = 0; i < nbMax; i++) {
			window.draw(playersRect[i]);
			window.draw(playersText[i]);
			if (i == playerIndex || ready[i]) {
				window.draw(circles[i]);
			}
			if (ready[i]) {
				check.setPosition(10, 340 + 60 * i);
				window.draw(check);
			}
		}

		if (selection == 1) {
			window.draw(leftArrow);
			window.draw(rightArrow);
		}

		buttons.draw(window);
		loading.draw(window);
		window.display();
	}
}
