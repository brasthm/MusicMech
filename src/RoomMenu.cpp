#include "RoomMenu.h"

#include "Graphics/LoadingScreen.h"
#include "System/RessourceLoader.h"
#include "Graphics/ButtonGroup.h"

#include <future>

bool RoomMenu::requestReady(Client* client, Game* game, SongDatabase* songs, sf::Uint32 color, bool load)
{
	if(load)
		game->loadFromCode(songs->getCurrentId(), songs->getSelectedPath());
		//game->loadFromFile(songs->getSelectedPath());

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

sf::Vector2f RoomMenu::getPositionInLayout(int nb, int index)
{
	float x, y;

	if (nb > 4) {
		if (index < 4) {
			y = 500;
		}
		else {
			y = 800;
		}
	}
	else {
		y = 600;
	}

	if (nb == 2) {
		x = (index + 1) * WIDOW_WIDTH / 3;
	}
	else {
		x = WIDOW_WIDTH / 8 + (index%4) * WIDOW_WIDTH / 4;
	}

	return sf::Vector2f(x, y);
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



	vignettebanner.setScale(0.3, 0.3);
	float hpos = 200, height = vignettebanner.getGlobalBounds().height;
	vignettebanner.setPosition(height, hpos);

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
		buttons.addButton(Button("BACK", "Back", COLOR_RED, 100, 970, 250, 70));
		buttons.addButton(Button("COLOR", "Choose Color", COLOR_YELLOW, 400, 970, 350, 70));
		buttons.addButton(Button("BEATMAP", "Change Beatmap", COLOR_BLUE, 800, 970, 400, 70));
		buttons.addButton(Button("READY", "Ready", COLOR_YELLOW, 1250, 970, 250, 70));
		buttons.addButton(Button("START", "Start", COLOR_GREEN, 1550, 970, 320, 70));
		buttons.setCurrent(3);
	}
	else {
		
		buttons.addButton(Button("BACK", "Back", COLOR_RED, 850, 970, 250, 70));
		buttons.addButton(Button("COLOR", "Choose Color", COLOR_YELLOW, 1150, 970, 350, 70));
		buttons.addButton(Button("READY", "Ready", COLOR_GREEN, 1550, 970, 320, 70));
		buttons.setCurrent(2);
	}

	


	sf::RectangleShape header;
	header.setSize({ WIDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(COLOR_YELLOW));

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


	int nbMax = client->getCurrentLobby().limit;

	std::vector<bool> ready(NB_MAX_JOUEURS);

	std::vector<sf::Uint32> colors;

	colors.emplace_back(0x3B00EAFF);
	colors.emplace_back(0x60FF0AFF);
	colors.emplace_back(0xFF3396FF);
	colors.emplace_back(0xFFF100FF);

	colors.emplace_back(0x9B2FDEFF);
	colors.emplace_back(0xFF3F0AFF);
	colors.emplace_back(0xF9E0DCFF);
	colors.emplace_back(0x65E2CDFF);

	std::vector<sf::CircleShape> circles;
	std::vector<Profile> profiles(NB_MAX_JOUEURS);

	for (int i = 0; i < NB_MAX_JOUEURS; i++) {
		circles.emplace_back(50.f, 500);
	}
	

	for (int i = 0; i < circles.size(); i++) {
		circles[i].setOutlineThickness(3);
		circles[i].setOutlineColor(sf::Color::Black);
		circles[i].setFillColor(sf::Color(colors[i]));
		//circles[i].setPosition(WIDOW_WIDTH * 0.5 - 100, 340 + 60 * i);
	}


	sf::CircleShape rightArrow(25.f, 3);
	rightArrow.setOrigin(25, 25);
	rightArrow.setRotation(90);
	rightArrow.setOutlineColor(sf::Color::Black);
	rightArrow.setOutlineThickness(3);


	sf::CircleShape leftArrow(25.f, 3);
	leftArrow.setOrigin(25, 25);
	leftArrow.setRotation(-90);
	leftArrow.setOutlineColor(sf::Color::Black);
	leftArrow.setOutlineThickness(3);

	artistText.setString(songs->getSelectedSong().artist);
	difficultyText.setString(songs->getSelectedSong().difficulty);
	difficultyText.setPosition(height / 2 - difficultyText.getGlobalBounds().width / 2, hpos + 10);
	artistRect.setSize({ artistText.getGlobalBounds().width + 100, height });

	sf::Sprite check(RessourceLoader::getTexture("Images/check.png"));

	std::future<bool> disconnect, refresh, beatmap, setReady, launchGame, waiting;

	int state = 0;

	int playerIndex = client->getPlayerIndex();
	int selectedColorIndex = playerIndex;
	int prevColorIndex = selectedColorIndex;
	sf::Uint32 selectedColor = colors[playerIndex];
	circles[playerIndex].setFillColor(sf::Color(selectedColor));


	for (int i = 0; i < nbMax; i++) {
		profiles[i].setProfile(client->getCurrentLobby().players[i]->name, client->getCurrentLobby().players[i]->bannerID, client->getCurrentLobby().players[i]->titleID);
		ready[i] = client->getCurrentLobby().players[i]->status == PlayerStatus::PLAYER_READY;
		if (ready[i])
			circles[i].setFillColor(sf::Color(client->getCurrentLobby().players[i]->color));
	}

	sf::Uint32 saveColor;

	if (creator && beatmapChanged) 
		beatmap = std::async(std::launch::async, &Client::requestBeatmapChange, client, songs->getSelectedSong().id, songs->getCurentNbPlayers());
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
					return -100;

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

		client->keepAlive();

		if (disconnect.valid() && disconnect.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			songs->stop();
			loading.stop();
			return -1;
		}

		if (refresh.valid() && refresh.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			std::cout << "Room refresh request" << std::endl;
			nbMax = client->getCurrentLobby().limit;
			if (songs->getSelectedSong().id != client->getCurrentLobby().beatmap) {
				songs->setSelectedById(client->getCurrentLobby().beatmap);
				vignettebanner.setTexture(RessourceLoader::getTexture(song.vignette));
				artistText.setString(songs->getSelectedSong().artist);
				difficultyText.setString(songs->getSelectedSong().difficulty);
				artistRect.setSize({ artistText.getGlobalBounds().width + 100, height });
				difficultyText.setPosition(height / 2 - difficultyText.getGlobalBounds().width / 2, hpos - difficultyText.getGlobalBounds().height / 2);


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
				profiles[i].setProfile(client->getCurrentLobby().players[i]->name, client->getCurrentLobby().players[i]->bannerID, client->getCurrentLobby().players[i]->titleID);
				ready[i] = client->getCurrentLobby().players[i]->status == PlayerStatus::PLAYER_READY;
				if (ready[i])
					circles[i].setFillColor(sf::Color(client->getCurrentLobby().players[i]->color));
				if (i == playerIndex) {

					for (int j = 0; j < colors.size(); j++) {
						if (colors[j] == client->getCurrentLobby().players[i]->color) {
							selectedColor = colors[j];
							selectedColorIndex = j;
							prevColorIndex = j;
						}
					}

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

		client->keepAlive();

		state = 0;
		if(!disconnect.valid() && !refresh.valid() && !beatmap.valid() && !setReady.valid() && !launchGame.valid() && !waiting.valid())
			client->monitorLobby(state, game->getEntityManager());

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
		window.draw(vignettebanner);
		window.draw(difficultyRect);
		window.draw(artistRect);

		window.draw(artistText);
		window.draw(difficultyText);

		

		for (int i = 0; i < nbMax; i++) {
			sf::Vector2f pos = getPositionInLayout(nbMax, i);

			sf::Sprite spr(profiles[i].getProfileCard().getTexture());
			spr.setPosition(pos.x - 200, pos.y - 100);
			window.draw(spr);

			if (i == playerIndex) {
				rightArrow.setPosition(pos.x - 120 , pos.y - 100);
				leftArrow.setPosition(pos.x - 280, pos.y - 100);
			}


			if (i == playerIndex || ready[i]) {
				circles[i].setPosition(pos.x - 250, pos.y - 150);
				window.draw(circles[i]);
			}
			if (ready[i]) {
				check.setPosition(pos.x - 200 - check.getGlobalBounds().width/2, pos.y - 100 - check.getGlobalBounds().height / 2);
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
