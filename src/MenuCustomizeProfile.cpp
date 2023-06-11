#include "MenuCustomizeProfile.h"

#include "Graphics/LoadingScreen.h"
#include "Graphics/FlexRectangle.h"
#include "Graphics/ButtonGroup.h"

#include "main.h"

RoomCustomizeProfile::RoomCustomizeProfile()
{
}

int RoomCustomizeProfile::run(sf::RenderWindow& window, BackgroundAnimation& bg, Profile& profile)
{
	sf::Clock fps;
	int exit = 0;

	sf::RectangleShape header;
	header.setSize({ WIDOW_WIDTH, 150 });
	header.setFillColor(sf::Color(COLOR_BLUE));

	sf::Text headerText;
	headerText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	headerText.setString("Change profile");
	headerText.setCharacterSize(108);
	headerText.setPosition(40, 10);
	headerText.setFillColor(sf::Color::Black);

	LoadingScreen loading;

	FlexRectangle movingSelector(920, 350, 880, 70);
	movingSelector.setFillColor(0xFFFFFF44);
	bool changed = false;
	int selected = 0;

	int mode = 0;

	std::string name;

	sf::Text anameText;
	sf::Text nameText, errorText;

	anameText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	anameText.setCharacterSize(40);
	anameText.setFillColor(sf::Color::Black);

	errorText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	errorText.setCharacterSize(40);
	errorText.setFillColor(sf::Color::Red);

	anameText.setString("");


	nameText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nameText.setString("New profile name");
	nameText.setCharacterSize(70);
	nameText.setPosition(200, 400);
	nameText.setFillColor(sf::Color::Black);

	anameText.setPosition(150 + nameText.getGlobalBounds().width + 220, 420);
	errorText.setPosition(400, 520);

	ButtonGroup buttons;
	buttons.addButton(Button("CANCEL", "Cancel", COLOR_RED, 1250, 970, 250, 70));
	buttons.addButton(Button("CONFIRM", "Confirm", COLOR_GREEN, 1550, 970, 320, 70));
	//buttons.setCurrent(1);


	sf::Text nameplateText, nameplateSelectionText;

	nameplateText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nameplateText.setString("Name plate");
	nameplateText.setCharacterSize(70);
	nameplateText.setFillColor(sf::Color::Black);
	nameplateText.setPosition(930, 250);

	nameplateSelectionText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	nameplateSelectionText.setString(BANNERS[profile.getBannerId()].name);
	nameplateSelectionText.setCharacterSize(50);
	nameplateSelectionText.setFillColor(sf::Color::Black);
	nameplateSelectionText.setPosition(WIDOW_WIDTH * 0.7 - nameplateSelectionText.getGlobalBounds().width / 2, 350);


	sf::Text titleText, titleSelectionText;

	titleText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	titleText.setString("Title");
	titleText.setCharacterSize(70);
	titleText.setFillColor(sf::Color::Black);
	titleText.setPosition(930, 500);

	titleSelectionText.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
	titleSelectionText.setString(TITLES[profile.getTitleId()] == "" ? "None": TITLES[profile.getTitleId()]);
	titleSelectionText.setCharacterSize(50);
	titleSelectionText.setFillColor(sf::Color::Black);
	titleSelectionText.setPosition(WIDOW_WIDTH * 0.7 - titleSelectionText.getGlobalBounds().width / 2, 600);


	sf::Text changeNameText;

	changeNameText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	changeNameText.setString("Change name");
	changeNameText.setCharacterSize(70);
	changeNameText.setFillColor(sf::Color::Black);
	changeNameText.setPosition(WIDOW_WIDTH * 0.7 - changeNameText.getGlobalBounds().width / 2, 750);


	sf::RectangleShape nameRect, nameFond;
	nameRect.setSize({ nameText.getGlobalBounds().width + 100 , 90 });
	nameRect.setFillColor(sf::Color(COLOR_YELLOW));
	nameRect.setPosition(150, 400);

	nameFond.setSize({ WIDOW_WIDTH * 0.4, 60 });
	nameFond.setFillColor(sf::Color(COLOR_SEMI_YELLOW));
	nameFond.setPosition(150 + nameText.getGlobalBounds().width + 200, 415);

	sf::RectangleShape cursor;
	cursor.setSize({ 5, 52 });
	cursor.setFillColor(sf::Color::White);

	sf::RectangleShape fond;
	fond.setFillColor(sf::Color(0x000000BB));
	fond.setSize({ WIDOW_WIDTH, WIDOW_HEIGHT });

	sf::RectangleShape menuFond;
	menuFond.setSize({ WIDOW_WIDTH *0.50, 700 });
	menuFond.setFillColor(sf::Color(COLOR_YELLOW));
	menuFond.setPosition(WIDOW_WIDTH * 0.45, WIDOW_HEIGHT - 850);


	sf::RectangleShape profilecardFond;
	profilecardFond.setSize({ nameplateText.getGlobalBounds().width + 50, nameplateText.getGlobalBounds().height + 25 });
	profilecardFond.setFillColor(sf::Color(COLOR_RED));
	profilecardFond.setPosition(nameplateText.getGlobalBounds().left - 20, nameplateText.getGlobalBounds().top - 20);

	sf::RectangleShape titleFond;
	titleFond.setSize({ titleText.getGlobalBounds().width + 50, titleText.getGlobalBounds().height + 30 });
	titleFond.setFillColor(sf::Color(COLOR_GREEN));
	titleFond.setPosition(titleText.getGlobalBounds().left - 20, titleText.getGlobalBounds().top - 20);

	sf::RectangleShape changenameFond;
	changenameFond.setSize({ changeNameText.getGlobalBounds().width + 50, changeNameText.getGlobalBounds().height + 25 });
	changenameFond.setFillColor(sf::Color(COLOR_BLUE));
	changenameFond.setPosition(changeNameText.getGlobalBounds().left - 20, changeNameText.getGlobalBounds().top - 20);


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

	int bannerSelection = profile.getBannerId(), oldBanner = bannerSelection;
	int titleSelection = profile.getTitleId(), oldTitle = titleSelection;
	std::string nameSelection = profile.getName(), oldName = nameSelection;


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
					if (mode == 0) {
						exit = -1;
						profile.setProfile(oldName, oldBanner, oldTitle);
					}
					if (mode == 1) {
						mode = 0;
						buttons.setCurrent(-1);
					}
				}


				if (mode == 1 && event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == '\b') {
						if (!name.empty()) name.erase(name.size() - 1, 1);
					}
					else if (event.text.unicode < 127 && event.text.unicode >= 20)
						name += event.text.unicode;
					anameText.setString(name);
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
					event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button != 6) {

					if (mode == 0) {
						if (selected == 3) {
							if (buttons.getCurrent() == "CANCEL") {
								exit = -1;
								profile.setProfile(oldName, oldBanner, oldTitle);
							}
							if (buttons.getCurrent() == "CONFIRM") {
								exit = 1;
								profile.save();
							}
						}
						if (selected == 2) {
							mode = 1;
							buttons.setCurrent(1);
						}
					}
					else if (mode == 1) {
						if (buttons.getCurrent() == "CONFIRM") {
							if (name.empty()) {
								errorText.setString("Please enter your name");
							}
							else if (name.size() > 10) {
								errorText.setString("Name must be between 1 and 10 characters");
							}
							else {
								nameSelection = name;
								profile.setProfile(nameSelection, bannerSelection, titleSelection);
								mode = 0;
								name = "";
								anameText.setString(name);
								buttons.setCurrent(-1);
							}
						}
						else if (buttons.getCurrent() == "CANCEL") {
							mode = 0;
							name = "";
							anameText.setString(name);
							buttons.setCurrent(-1);
						}
					}
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
					if (mode == 0) {
						if (selected != 0) {
							selected--;
							changed = true;
						}
					}

				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {
					if (mode == 0) {
						if (selected != 3) {
							selected++;
							changed = true;
						}
					}
				}

				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
					if (mode == 0) {
						if (selected == 0) {
							bannerSelection--;
							if (bannerSelection == 0) bannerSelection = BANNERS.size() - 1;

							nameplateSelectionText.setString(BANNERS[bannerSelection].name);
							nameplateSelectionText.setPosition(WIDOW_WIDTH * 0.7 - nameplateSelectionText.getGlobalBounds().width / 2, 350);

							profile.setProfile(nameSelection, bannerSelection, titleSelection);
						}
						if (selected == 1) {
							titleSelection--;
							if (titleSelection == -1) titleSelection = TITLES.size() - 1;

							titleSelectionText.setString(TITLES[titleSelection] == "" ? "None" : TITLES[titleSelection]);
							titleSelectionText.setPosition(WIDOW_WIDTH * 0.7 - titleSelectionText.getGlobalBounds().width / 2, 600);

							profile.setProfile(nameSelection, bannerSelection, titleSelection);
						}
						if (selected == 3) {
							buttons.prev();
						}
					}
					if (mode == 1) {
						buttons.prev();
					}
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
					event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
					if (mode == 0) {
						if (selected == 0) {
							bannerSelection++;
							bannerSelection = bannerSelection % BANNERS.size();
							if (bannerSelection == 0) bannerSelection = 1;

							nameplateSelectionText.setString(BANNERS[bannerSelection].name);
							nameplateSelectionText.setPosition(WIDOW_WIDTH * 0.7 - nameplateSelectionText.getGlobalBounds().width / 2, 350);

							profile.setProfile(nameSelection, bannerSelection, titleSelection);
						}
						if (selected == 1) {
							titleSelection++;
							titleSelection = titleSelection % TITLES.size();

							titleSelectionText.setString(TITLES[titleSelection] == "" ? "None" : TITLES[titleSelection]);
							titleSelectionText.setPosition(WIDOW_WIDTH * 0.7 - titleSelectionText.getGlobalBounds().width / 2, 600);

							profile.setProfile(nameSelection, bannerSelection, titleSelection);
						}
						if (selected == 3) {
							buttons.next();
						}
					}
					if (mode == 1) {
						buttons.next();
					}
				}
			}
		}

		if (changed) {

			if (selected == 0) {
				movingSelector.setPos(sf::Vector2f(920, 350));
				movingSelector.setSize(sf::Vector2f(880, 70));
				buttons.setCurrent(-1);
			}
			else if (selected == 1) {
				movingSelector.setPos(sf::Vector2f(920, 600));
				movingSelector.setSize(sf::Vector2f(880, 70));
				buttons.setCurrent(-1);
			}
			else if (selected == 2) {
				movingSelector.setPos(sf::Vector2f(900, 750));
				movingSelector.setSize(sf::Vector2f(880, 100));
				buttons.setCurrent(-1);
			}
			else if (selected == 3) {
				buttons.setCurrent(1);
			}

			changed = false;
		}

		bg.update(elapsedTime);
		movingSelector.update(elapsedTime);
		loading.update(elapsedTime);
		buttons.update(elapsedTime);


		window.clear(sf::Color(0x2A2431FF));
		bg.draw(window);

		window.draw(header);
		window.draw(headerText);

		window.draw(menuFond);
		window.draw(profilecardFond);
		window.draw(titleFond);
		window.draw(changenameFond);

		window.draw(nameplateText);
		window.draw(nameplateSelectionText);

		window.draw(titleText);
		window.draw(titleSelectionText);

		window.draw(changeNameText);

		
		if (mode == 1) {
			if (name.empty())
				cursor.setPosition(150 + nameText.getGlobalBounds().width + 220 + 5, 420);
			else
				cursor.setPosition(anameText.getGlobalBounds().left + anameText.getGlobalBounds().width + 5, 420);
		}

		sf::Sprite spr(profile.getProfileCard().getTexture());
		spr.setPosition(200, 470);
		window.draw(spr);

		if (selected == 0) {
			leftArrow.setPosition(970, 390);
			rightArrow.setPosition(1730, 390);

			window.draw(leftArrow);
			window.draw(rightArrow);
		}
		if (selected == 1) {
			leftArrow.setPosition(970, 640);
			rightArrow.setPosition(1730, 640);

			window.draw(leftArrow);
			window.draw(rightArrow);
		}

		if (selected != 3) {
			movingSelector.draw(window);
		}
		


		if (mode == 1) {
			window.draw(fond);
			window.draw(nameRect);
			window.draw(nameFond);
			window.draw(anameText);
			window.draw(nameText);
			
			window.draw(cursor);
			window.draw(errorText);

		}

		buttons.draw(window);

		loading.draw(window);
		window.display();
	}

	return exit;
}
