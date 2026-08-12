#include "EndScreen.h"
#include "Graphics/LoadingScreen.h"
#include "System/RessourceLoader.h"
#include "System/StatisticCounter.h"
#include "Graphics/ButtonGroup.h"
#include "main.h"
#include "STRINGS.h"

void EndScreen::draw_markers(sf::RenderWindow& window, sf::Vector2f position)
{

	float p = 0.35;
	float r = 25;

	sf::RectangleShape r1;

	r1.setSize(sf::Vector2f(r * 1.5, 10));
	r1.setOrigin(r * 0.75, 5);
	

	sf::CircleShape shape;

	shape.setRadius(r);
	shape.setFillColor(sf::Color(COLOR_RED));
	shape.setPointCount(100);


	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setFillColor(sf::Color(COLOR_RED));


	float y1 = p * r;
	float x1 = r * sqrt(1 - p * p);
	float alpha = asin(p);

	float b = x1 / tan(alpha) - y1;

	shape.setPosition(position - sf::Vector2f(r, r + b));
	r1.setPosition(position - sf::Vector2f(0, b));

	triangle.setPoint(0, position + sf::Vector2f(-x1, y1 - b));
	triangle.setPoint(1, position + sf::Vector2f(x1, y1 - b));
	triangle.setPoint(2, position + sf::Vector2f(0, 0));

	window.draw(shape);
	window.draw(triangle);
	r1.setRotation(45);
	window.draw(r1);
	r1.setRotation(-45);
	window.draw(r1);
}

void EndScreen::draw_deaths(sf::RenderWindow& window, Song* song)
{
	float d1 = WINDOW_WIDTH * 0.1, d2 = WINDOW_WIDTH*0.9;
	float y = 290;

	sf::Text deathCounter;

	deathCounter.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	deathCounter.setString("Retries: " + std::to_string((int)StatisticCounter::get(STATISTIC_DEATHCOUNTER, 0)));
	deathCounter.setCharacterSize(52);
	deathCounter.setPosition(10, 100);
	deathCounter.setFillColor(sf::Color::White);

	window.draw(deathCounter);

	sf::RectangleShape line;
	line.setSize({ d2 -d1, 7 });
	line.setFillColor(sf::Color(COLOR_YELLOW));
	line.setPosition(d1, y - 3);

	window.draw(line);

	sf::CircleShape shape;
	shape.setRadius(15);

	float length = song->getIndexCheckpoint(song->getMaxCheckpoint() - 1).second;

	shape.setFillColor(sf::Color(COLOR_YELLOW));

	for (int i = 0; i < song->getMaxCheckpoint(); i++) {
		shape.setPosition((d2 - d1) * song->getIndexCheckpoint(i).second / length + d1 - 15, y - 15);
		window.draw(shape);
	}

	if (StatisticCounter::get(STATISTIC_DEATHCOUNTER, 0) == 0) {
		sf::Text oneShotText;

		oneShotText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
		oneShotText.setString("One shot!");
		oneShotText.setCharacterSize(92);
		oneShotText.setPosition(WINDOW_WIDTH/2 - oneShotText.getGlobalBounds().width/2, y - 40 - 92);
		oneShotText.setFillColor(sf::Color(COLOR_RED));

		window.draw(oneShotText);
	}
	else {
		for (int i = 0; i < StatisticCounter::getTimestampSize(TIMESTAMPS_FAILED); i++) {
			float fraction = StatisticCounter::getTimestamp(TIMESTAMPS_FAILED, i) / length;
			draw_markers(window, sf::Vector2f(d1 + (d2 - d1) * fraction, y - 17));
		}
	}
	


}

int EndScreen::run(sf::RenderWindow& window, BackgroundAnimation& bg, Client* client, SongDatabase& songs, Song* currentSong)
{
	sf::Clock fps;

	LoadingScreen loading;

	StatisticCounter::sortTimestamp(0);

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

	if (WINDOW_WIDTH - img.getGlobalBounds().width > WINDOW_HEIGHT - img.getGlobalBounds().height)
		finalImage.setScale(WINDOW_WIDTH / (float)img.getGlobalBounds().width, WINDOW_WIDTH / (float)img.getGlobalBounds().width);
	else if (WINDOW_WIDTH - img.getGlobalBounds().width < WINDOW_HEIGHT - img.getGlobalBounds().height)
		finalImage.setScale(WINDOW_HEIGHT / (float)img.getGlobalBounds().height, WINDOW_HEIGHT / (float)img.getGlobalBounds().height);

	sf::RenderTexture objText, mvpRenderText;	

	sf::Text obj1Text, obj2Text, obj3Text;

	obj1Text.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	obj1Text.setString("Clear the song");
	obj1Text.setCharacterSize(72);
	obj1Text.setPosition(80, 200);
	obj1Text.setFillColor(sf::Color::Black);

	sf::RectangleShape obj1;
	obj1.setSize({ WINDOW_WIDTH * 0.9, 90 });
	obj1.setFillColor(sf::Color(COLOR_GREEN));
	obj1.setPosition(60, 200);

	obj2Text.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	obj2Text.setString("Clear the song without getting hit");
	obj2Text.setCharacterSize(72);
	obj2Text.setPosition(80, 320);
	obj2Text.setFillColor(sf::Color::Black);

	sf::RectangleShape obj2;
	obj2.setSize({ WINDOW_WIDTH * 0.9, 90 });
	obj2.setFillColor(sf::Color(COLOR_RED));
	obj2.setPosition(60, 320);


	obj3Text.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	obj3Text.setString("Clear the song without retrying");
	obj3Text.setCharacterSize(72);
	obj3Text.setPosition(80, 440);
	obj3Text.setFillColor(sf::Color::Black);

	sf::RectangleShape obj3;
	obj3.setSize({ WINDOW_WIDTH * 0.9, 90 });
	obj3.setFillColor(sf::Color(COLOR_RED));
	obj3.setPosition(60, 440);


	sf::Text objectivesText;
	objectivesText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	objectivesText.setString("Objectives");
	objectivesText.setCharacterSize(108);
	objectivesText.setPosition(40, 10);
	objectivesText.setFillColor(sf::Color::Black);


	sf::Text mvpText;
	mvpText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	mvpText.setCharacterSize(108);
	mvpText.setFillColor(sf::Color::Black);

	ButtonGroup buttons;
	buttons.addButton(Button("NEXT", "Next", COLOR_GREEN, 1550, 970, 320, 70));
	buttons.setCurrent(-1);


	vignettebanner.setScale(0.3, 0.3);
	float hpos = 25, height = vignettebanner.getGlobalBounds().height;
	vignettebanner.setPosition(height, hpos);



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


	if (StatisticCounter::get(STATISTIC_FAILED, client->getPlayerIndex()) == 0) {
		obj2.setFillColor(sf::Color(COLOR_GREEN));
	}

	if (StatisticCounter::get(STATISTIC_DEATHCOUNTER, 0) == 0) {
		obj3.setFillColor(sf::Color(COLOR_GREEN));
	}

	Profile mvp, mvp2;


	if (StatisticCounter::getPlayerNumber() == 1) {

	}
	else if (StatisticCounter::getPlayerNumber() == 2) {

	}
	else {
		std::vector<std::tuple<int, int, float, bool>> allOutliers;

		for (auto stat : ALL_TRACKED_STATS) {
			std::pair<int, float> most = StatisticCounter::getOutlier(stat, true), least = StatisticCounter::getOutlier(stat, false);
			
			most.second = abs(most.second);
			least.second = abs(least.second);

			allOutliers.emplace_back(most.second > least.second ? std::make_tuple(stat, most.first, most.second, false) : std::make_tuple(stat, least.first, least.second, true));
		}

		std::sort(allOutliers.begin(), allOutliers.end(), [](std::tuple<int, int, float, bool> a, std::tuple<int, int, float, bool> b) {
			return std::get<2>(a) > std::get<2>(b);
		});

		int mvpStat = std::get<0>(allOutliers[0]);
		int mvpPlayer = std::get<1>(allOutliers[0]);
		bool mvpBool = std::get<3>(allOutliers[0]);
		mvp.setProfile(client->getCurrentLobby().players[mvpPlayer]->name, client->getCurrentLobby().players[mvpPlayer]->bannerID, client->getCurrentLobby().players[mvpPlayer]->titleID);
		std::cout << "MVP : " << mvpPlayer << " (" << getTitleByStatistic(mvpStat, mvpBool) << ")" << std::endl;

		mvpText.setString(getTitleByStatistic(mvpStat, mvpBool));
		mvpText.setPosition(2 * WINDOW_WIDTH / 4 - mvpText.getGlobalBounds().width / 2, 10);
	}

	IFloat objwidth(WINDOW_WIDTH);

	int nb = 0;
	

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
						nb++;
						objwidth.set(0, 0.5);
						if(nb == 2)
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
		objwidth.update(elapsedTime);

		loading.update(elapsedTime);
		buttons.update(elapsedTime);

		window.clear(sf::Color(0x2A2431FF));

		window.draw(finalImage);
		bg.draw(window);

		if (objwidth.get() > 1) {
			objText.create(objwidth.get(), 600);
			objText.clear(sf::Color(COLOR_YELLOW));


			objText.draw(obj1);
			objText.draw(obj1Text);
			objText.draw(obj2);
			objText.draw(obj2Text);
			objText.draw(obj3);
			objText.draw(obj3Text);
			objText.draw(objectivesText);

			objText.display();

			sf::Sprite objRect(objText.getTexture());
			objRect.setPosition(0, 330);
			window.draw(objRect);
		}
		if (objwidth.get() < WINDOW_WIDTH) {
			mvpRenderText.create(WINDOW_WIDTH - objwidth.get(), 600);
			mvpRenderText.clear(sf::Color(COLOR_BLUE));

			mvpRenderText.draw(mvpText);
			sf::Sprite mvpProfile(mvp.getProfileCard().getTexture());
			mvpProfile.setPosition(WINDOW_WIDTH/2 - mvpProfile.getGlobalBounds().width/2, 230);
			mvpRenderText.draw(mvpProfile);

			mvpRenderText.display();

			sf::Sprite mvpRect(mvpRenderText.getTexture());
			mvpRect.setPosition(objwidth.get(), 330);
			window.draw(mvpRect);
		}


		window.draw(vignettebanner);
		window.draw(difficultyRect);
		window.draw(artistRect);
		window.draw(artistText);
		window.draw(difficultyText);


		draw_deaths(window, currentSong);

		buttons.draw(window);
		loading.draw(window);

		


		window.display();
	}

	return 0;
}
