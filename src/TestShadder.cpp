#include "TestShadder.h"

TestShadder::TestShadder()
{
}

int TestShadder::run(sf::RenderWindow& window, BackgroundAnimation& bg)
{

	Profile profile;
	profile.setProfile("Kuku", BANNER_GREEN, TITLE_PANICKED);
	sf::Clock fps, time;
	int exit = 0;

	sf::RectangleShape header;
	header.setSize({ WIDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(COLOR_BLUE));

	sf::Text headerText;
	headerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	headerText.setString("Test Shadder");
	headerText.setCharacterSize(108);
	headerText.setPosition(0, 0);
	headerText.setFillColor(sf::Color::Black);

	sf::RenderTexture rt;
	rt.create(headerText.getGlobalBounds().width, 150);

	sf::Shader shader;

	shader.loadFromFile(RessourceLoader::getPath("Shader/test.frag"), sf::Shader::Fragment);
	//shader.loadFromFile(RessourceLoader::getPath("Shader/test.vert"), sf::Shader::Vertex);

	while (exit == 0)
	{
		sf::Time elapsedTime = fps.getElapsedTime();
		fps.restart();

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				exit = -100;
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				exit = -1;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
				shader.loadFromFile(RessourceLoader::getPath("Shader/test.frag"), sf::Shader::Fragment);
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F6) {
				shader.loadFromFile(RessourceLoader::getPath("Shader/test.vert"), sf::Shader::Vertex);
			}
			
		}

		bg.update(elapsedTime);

		shader.setUniform("time", time.getElapsedTime().asSeconds());

		window.clear(sf::Color(0x2A2431FF));
		bg.draw(window);

		window.draw(header);
		rt.clear(sf::Color::Transparent);
		rt.draw(headerText);
		rt.display();

		sf::Sprite sp(rt.getTexture());
		sp.setPosition(40, 10);
		window.draw(sp, &shader);

		sf::Sprite spr(profile.getProfileCard().getTexture());
		spr.setPosition(200, 470);
		window.draw(spr, &shader);

		window.display();
	}

	return exit;
}
