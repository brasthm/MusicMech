#include "LobbySelection.h"

#include "System/RessourceLoader.h"
#include "Graphics/ButtonGroup.h"
#include "Graphics/FlexRectangle.h"
#include "Graphics/LoadingScreen.h"
#include "Network/Lobby.h"
#include "Network/Client.h"

#include "main.h"

#include <future>

bool LobbySelection::requestJoinRoom(Client* client, int selection)
{
	bool ok = true;
	ok = client->requestLobbyJoin(client->getLobby(selection).id);

	int state = 0;

	if (!ok) return false;

	while (state == 0) {
		client->monitorLobby(state);
	}

	if (state == 2) {
		client->requestLobbyInfo(client->getLobbyIndex());
	}
	else
		return false;

	return true;
}

LobbySelection::LobbySelection()
{
	
}

LobbySelection::~LobbySelection()
{
	
}

int LobbySelection::run(sf::RenderWindow& window, BackgroundAnimation& bg, Client *client, SongDatabase& songs)
{

	sf::Clock fps;
	bool exit = false, focus = false, first = true;

	int selection = 0;
	int decalage = 0;

	LoadingScreen loading;


	sf::RectangleShape moving;
	moving.setPosition(0, 335);
	moving.setSize({ WIDOW_WIDTH, 52 });
	moving.setFillColor(sf::Color(0xFFFFFF44));

	sf::Text roomText, headerText;
	sf::Text nameText, playerText, nbText;

	roomText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	roomText.setCharacterSize(40);
	roomText.setFillColor(sf::Color::Black);

	nameText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nameText.setString("Room name");
	nameText.setCharacterSize(70);
	nameText.setPosition(60, 240);
	nameText.setFillColor(sf::Color::Black);

	playerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	playerText.setString("Player");
	playerText.setCharacterSize(70);
	playerText.setPosition(60 + WIDOW_WIDTH * 0.6, 240);
	playerText.setFillColor(sf::Color::Black);

	nbText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nbText.setString("#");
	nbText.setCharacterSize(70);
	nbText.setPosition(60 + WIDOW_WIDTH * 0.9, 240);
	nbText.setFillColor(sf::Color::Black);

	headerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	headerText.setString("Room Selection");
	headerText.setCharacterSize(108);
	headerText.setPosition(40, 10);
	headerText.setFillColor(sf::Color::Black);



	ButtonGroup buttons;
	buttons.addButton(Button("REFRESH", "Refresh", 0xf7dd72ff, 1250, 970, 250, 70));
	buttons.addButton(Button("CREATE", "Create room", 0xa5c882ff, 1550, 970, 320, 70));


	sf::RectangleShape header;
	header.setSize({ WIDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(0xff6392ff));


	sf::RectangleShape nameRect, nameFond;
	nameRect.setSize({ WIDOW_WIDTH *0.6, 100 });
	nameRect.setFillColor(sf::Color(0x5ab1bbff));
	nameRect.setPosition(0, 230);

	nameFond.setSize({ WIDOW_WIDTH * 0.6, 610 });
	nameFond.setFillColor(sf::Color(0x5ab1bb88));
	nameFond.setPosition(0, 330);

	sf::RectangleShape playerRect, playerFond;
	playerRect.setSize({ WIDOW_WIDTH * 0.3, 100 });
	playerRect.setFillColor(sf::Color(0xa5c882ff));
	playerRect.setPosition(WIDOW_WIDTH * 0.6, 230);

	playerFond.setSize({ WIDOW_WIDTH * 0.3, 610 });
	playerFond.setFillColor(sf::Color(0xa5c88288));
	playerFond.setPosition(WIDOW_WIDTH * 0.6, 330);

	sf::RectangleShape nbRect, nbFond;
	nbRect.setSize({ WIDOW_WIDTH * 0.1, 100 });
	nbRect.setFillColor(sf::Color(0xf7dd72ff));
	nbRect.setPosition(WIDOW_WIDTH * 0.9, 230);

	nbFond.setSize({ WIDOW_WIDTH * 0.1, 610 });
	nbFond.setFillColor(sf::Color(0xf7dd7288));
	nbFond.setPosition(WIDOW_WIDTH * 0.9, 330);


	std::vector<std::string> listname, listplayer, listnb;
	std::vector<int> listind;

	std::future<bool> refreshList = std::async(std::launch::async, &Client::requestLobbyList, client), joinRoom;
	loading.start("Fetching data");
	int save;


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

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1)
					return -1;
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0) {
					if (!focus) {
						auto res = buttons.getCurrent();
						if (res == "REFRESH") {
							refreshList = std::async(std::launch::async, &Client::requestLobbyList, client);
							loading.start("Fetching data");
						}
						else if (res == "CREATE") {
							return 1;
						}
					}
					else {
						save = listind[selection];
						joinRoom = std::async(std::launch::async, &LobbySelection::requestJoinRoom, this, client, save);
						loading.start("Joining room");
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
					if (!focus) {
						focus = true;
						buttons.setCurrent(-1);
					}
					else {
						selection--;
						if (selection < 0)
							selection = 0;
						if (selection != 0 && selection - decalage == 0) {
							decalage--;
						}
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {
					if (!focus) {
						focus = true;
						buttons.setCurrent(-1);
					}
					else {
						selection++;
						if (selection >= listname.size()) {
							selection =  listname.size() - 1 > 0 ? listname.size() - 1:0;
							focus = false;
							buttons.setCurrent(0);
						}

						if (selection == 12 + decalage) {
							decalage++;
						}
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
					if (focus || first) {
						focus = false;
						first = false;
						buttons.setCurrent(0);
					}
					else {
						buttons.prev();
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
					if (focus || first) {
						focus = false;
						first = false;
						buttons.setCurrent(1);
					}
					else {
						buttons.next();
					}
				}
			}
		}

		if (refreshList.valid() && refreshList.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			listname.clear();
			listplayer.clear();
			listnb.clear();
			for (int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
				Lobby l = client->getLobby(i);
				if (l.status != LOBBY_AVAILABLE) {
					listname.emplace_back(l.name);
					listplayer.emplace_back(l.players[0]->name);
					listnb.emplace_back(std::to_string(l.nbIn) + "/" + std::to_string(l.limit));
					listind.push_back(i);
				}
			}
			refreshList = std::future<bool>();
			loading.stop();
		}

		if (joinRoom.valid() && joinRoom.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			songs.setMode(client->getCurrentLobby().mode);
			songs.setSelectedById(client->getCurrentLobby().beatmap);
			loading.stop();
			return joinRoom.get() ? 2:-1;
		}

		bg.update(elapsedTime);

		loading.update(elapsedTime);
		buttons.update(elapsedTime);

		moving.setPosition({ 0, 335.f + 50 * (selection-decalage) });


		window.clear(sf::Color(0x2A2431FF));

		bg.draw(window);
		window.draw(header);
		window.draw(headerText);
		window.draw(nameRect);
		window.draw(playerRect);
		window.draw(nbRect);
		window.draw(nameFond);
		window.draw(playerFond);
		window.draw(nbFond);

		window.draw(nameText);
		window.draw(playerText);
		window.draw(nbText);

		//moving.draw(window);
		if(focus) window.draw(moving);

		for (int i = decalage; i < listname.size(); i++) {
			if (i - decalage >= 12) break;
			if (focus && i == selection) {
				roomText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
			}
			else {
				roomText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
			}
			roomText.setString(listname[i]);
			roomText.setPosition(10, 338 + (i - decalage) * 50);
			window.draw(roomText);
			roomText.setString(listplayer[i]);
			roomText.setPosition(10 + WIDOW_WIDTH * 0.6, 338 + (i - decalage) * 50);
			window.draw(roomText);
			roomText.setString(listnb[i]);
			roomText.setPosition(10 + WIDOW_WIDTH * 0.9, 338 + (i - decalage) * 50);
			window.draw(roomText);
		}
		
		buttons.draw(window);
		loading.draw(window);
		window.display();
	}
	return 0;
}


