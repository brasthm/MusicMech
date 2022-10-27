#include "RoomCreation.h"

#include "Graphics/LoadingScreen.h"
#include "System/RessourceLoader.h"
#include "Graphics/ButtonGroup.h"

#include <future>

bool RoomCreation::request(Client* client, std::string name, std::string beatmap, std::string mode)
{
	bool ok = false;
	ok = client->requestLobbyCreation(name, beatmap, mode);
	ok = ok && client->requestLobbyInfo(client->getLobbyIndex());
	return ok;
}

int RoomCreation::run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, SongDatabase& songs, std::string &roomName)
{
	sf::Clock fps;
	bool exit = false, focus = false, first = true;

	int selection = 0;

	LoadingScreen loading;

	SongData song = songs.getSelectedSong();
	if(!songs.isPlaying())
		songs.play();

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



	FlexRectangle moving(50, 280, WIDOW_WIDTH * 0.95, 130);
	//FlexRectangle moving(100, 540, WIDOW_WIDTH * 0.93, 200);
	moving.setFillColor(0xFFFFFF44);

	sf::Text roomText, headerText;
	sf::Text nameText, beatmapText, nbText;

	roomText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	roomText.setCharacterSize(40);
	roomText.setFillColor(sf::Color::Black);

	nameText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nameText.setString("Room name");
	nameText.setCharacterSize(70);
	nameText.setPosition(140, 300);
	nameText.setFillColor(sf::Color::Black);

	beatmapText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	beatmapText.setString("Beatmap");
	beatmapText.setCharacterSize(70);
	beatmapText.setPosition(190, 600);
	beatmapText.setFillColor(sf::Color::Black);

	nbText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nbText.setString(songs.getCurentNbPlayers()+"P");
	nbText.setCharacterSize(80);
	nbText.setFillColor(sf::Color::Black);


	headerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	headerText.setString("Room Creation");
	headerText.setCharacterSize(108);
	headerText.setPosition(40, 10);
	headerText.setFillColor(sf::Color::Black);



	ButtonGroup buttons;
	buttons.addButton(Button("CANCEL", "Cancel", 0xff6392ff, 1250, 970, 250, 70));
	buttons.addButton(Button("CREATE", "Create room", 0xa5c882ff, 1550, 970, 320, 70));


	sf::RectangleShape header;
	header.setSize({ WIDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(0x5ab1bbff));


	sf::RectangleShape cursor;
	cursor.setSize({ 5, 52 });
	cursor.setFillColor(sf::Color::White);

	sf::RectangleShape nameRect, nameFond;
	nameRect.setSize({ nameText.getGlobalBounds().width + 100 , 90 });
	nameRect.setFillColor(sf::Color(0xf7dd72ff));
	nameRect.setPosition(100, 300);

	nameFond.setSize({ WIDOW_WIDTH * 0.6, 60 });
	nameFond.setFillColor(sf::Color(0xf7dd7288));
	nameFond.setPosition(100 + nameText.getGlobalBounds().width + 200, 315);

	sf::RectangleShape beatmapRect, beatmapFond;
	beatmapRect.setSize({ beatmapText.getGlobalBounds().width + 100, 90 });
	beatmapRect.setFillColor(sf::Color(0xa5c882ff));
	beatmapRect.setPosition(150, 600);

	sf::Sprite vignette(RessourceLoader::getTexture(song.vignette));
	vignette.setScale(0.5f, 0.5f);
	vignette.setPosition(100 + nameText.getGlobalBounds().width + 250, 580);

	beatmapFond.setSize({ WIDOW_WIDTH * 0.6f + nameFond.getGlobalBounds().left
		- vignette.getGlobalBounds().left - vignette.getGlobalBounds().width,
		vignette.getGlobalBounds().height});
	if(songs.getCurentNbPlayers() == "4")
		beatmapFond.setFillColor(sf::Color(0xff6392ff));
	else if(songs.getCurentNbPlayers() == "2")
		beatmapFond.setFillColor(sf::Color(0xa5c882ff));
	else if(songs.getCurentNbPlayers() == "8")
		beatmapFond.setFillColor(sf::Color(0x5ab1bbff));

	beatmapFond.setPosition(vignette.getGlobalBounds().left + vignette.getGlobalBounds().width, vignette.getGlobalBounds().top);

	nbText.setPosition(beatmapFond.getGlobalBounds().left + beatmapFond.getGlobalBounds().width/2 - nbText.getGlobalBounds().width/2,
		beatmapFond.getGlobalBounds().top + 15);

	roomText.setPosition(100 + nameText.getGlobalBounds().width + 220, 320);
	roomText.setString(roomName);


	std::future<bool> createRoom;

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
				if (focus && event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b') {
						if (!roomName.empty()) roomName.erase(roomName.size() - 1, 1);
					}
					else if(event.text.unicode < 127 && event.text.unicode >= 20)
						roomName += event.text.unicode;
					roomText.setString(roomName);
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1) {
					if (focus) 
						focus = false;
					else {
						exit = true;
						songs.stop();
						return -1;
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0) {
					if (selection == 0) {
						focus = !focus;
					}
					else if (selection == 1) {
						return 1;
					}
					else if (selection == 2) {
						auto reponse = buttons.getCurrent();
						if (reponse == "CANCEL") {
							songs.stop();
							return -1;
						}
						if (reponse == "CREATE") {
							if (roomName != "") {
								createRoom = std::async(std::launch::async, &RoomCreation::request, this, client, roomName, songs.getSelectedSong().id, songs.getCurentNbPlayers());
								loading.start("Creating room");
							}
						}
					}
				}
				if (!focus) {
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
						event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
						selection--;
						if (selection < 0) selection = 0;
						else if (selection == 0) {
							moving.setPos({ 50, 280 });
							moving.setSize({ WIDOW_WIDTH * 0.95, 130 });
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
							moving.setPos({ 100, 540 });
							moving.setSize({ WIDOW_WIDTH * 0.93, 200 });
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

		if (roomName.empty())
			cursor.setPosition(100 + nameText.getGlobalBounds().width + 220 + 5 , 320);
		else
			cursor.setPosition(roomText.getGlobalBounds().left + roomText.getGlobalBounds().width + 5, 320);

		if (createRoom.valid() && createRoom.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			if (createRoom.get())
				return 2;
			loading.stop();
		}

		bg.update(elapsedTime);

		loading.update(elapsedTime);
		buttons.update(elapsedTime);
		moving.update(elapsedTime);

		window.clear(sf::Color(0x2A2431FF));

		window.draw(finalImage);
		bg.draw(window);
		if(selection != 2)
			moving.draw(window);
		window.draw(header);
		window.draw(headerText);
		window.draw(nameRect);
		window.draw(nameFond);
		window.draw(nameText);
		window.draw(beatmapRect);
		window.draw(beatmapText);
		window.draw(vignette);
		window.draw(beatmapFond);
		window.draw(nbText);
		if (focus) {
			window.draw(cursor);
		}
		window.draw(roomText);
		
		
		buttons.draw(window);
		loading.draw(window);
		window.display();
	}

	return 0;
}
