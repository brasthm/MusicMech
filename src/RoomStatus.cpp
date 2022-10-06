#include "RoomStatus.h"

#include "System/RessourceLoader.h"
#include "Graphics/ButtonGroup.h"

RoomStatus::RoomStatus(Song* song, std::vector<Mechanic*> *mechanicList)
{
    joueurs_.clear();
    totems_.clear();
    em_.clear();

    beat_ = 0;

    
    for (int i = 0; i < NB_MAX_JOUEURS; i++) {
        joueurs_.emplace_back();
    }

    for (int i = 0; i < NB_MAX_TOTEM; i++) {
        totems_.emplace_back();
    }

    for (int i = 0; i < NB_MAX_JOUEURS; i++) {
        em_.addPlayer(std::addressof(joueurs_[i]));
    }
    for (int i = 0; i < NB_MAX_TOTEM; i++) {
        em_.addTotem(std::addressof(totems_[i]));
    }

    for (int i = 0; i < mechanicList->size(); i++) {
        mechanicList_.emplace_back();
        mechanicList_.back() = mechanicList->at(i)->clone();
    }

    em_.addArena(&arena_);

    song_ = song;
}

RoomStatus::~RoomStatus()
{
    for (int i = 0; i < mechanicList_.size(); i++) {
        delete mechanicList_[i];
    }
}

int RoomStatus::run(sf::RenderWindow& window, Client* client)
{
    bool exit = false;

    float currentBeat = beat_;

    sf::Clock fps;

    int mode = 0; // 0 - ALL, 1 - KILL ONLY, 2 - PREV ONLY

    for (int i = 0; i < joueurs_.size(); i++) {
        joueurs_[i].showPlate(true);
    }

    std::vector<sf::RectangleShape> namesInfo;
    std::vector<sf::Text> namesText;

    for (int i = 0; i < joueurs_.size(); i++) {
        namesText.emplace_back();
        namesInfo.emplace_back();

        namesText.back().setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
        namesText.back().setCharacterSize(35);
        namesText.back().setString(joueurs_[i].getName());
        namesText.back().setFillColor(sf::Color::Black);

        namesInfo.back().setFillColor(sf::Color(joueurs_[i].getColor()));
        auto size = namesText.back().getGlobalBounds();
        namesInfo.back().setSize(sf::Vector2f(size.width + 20, size.height + 15));

        namesText.back().setPosition(5, WIDOW_HEIGHT - 50 - (joueurs_.size() - i) * (60));
        namesInfo.back().setPosition(0, WIDOW_HEIGHT - 50 - (joueurs_.size() - i) * (60));
    }

    ButtonGroup menuButtons;

    menuButtons.addButton(Button("SHOWALL",    "Show all notes",    0xa5c882ff, 0, 100, 225, 50));
    menuButtons.addButton(Button("SHOWFAILED", "Show failed notes", 0xa5c882ff, 0, 170, 263, 50));
    menuButtons.addButton(Button("HIDE",       "Hide future notes", 0xa5c882ff, 0, 240, 257, 50));
    menuButtons.addButton(Button("DEBUFF",     "Inspect debuffs",   0xf7dd72ff, 0, 310, 230, 50));
    menuButtons.addButton(Button("RESET",      "Reset",             0x5ab1bbff, 0, 380, 90, 50));
    menuButtons.addButton(Button("QUIT",       "Back",              0xff6392ff, 0, 450, 80, 50));

    std::pair<float, float> checkpoint;

    sf::RenderTexture renderText;
    renderText.create(WIDOW_WIDTH, WIDOW_HEIGHT);

    while (!exit) {
        sf::Time elapsedTime = fps.getElapsedTime();


        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                return -1;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
                event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0) {
                if (menuButtons.getCurrent() == "SHOWALL") {
                    mode = 0;
                }
                else if (menuButtons.getCurrent() == "SHOWFAILED") {
                    mode = 1;
                }
                else if (menuButtons.getCurrent() == "HIDE") {
                    mode = 2;
                }
                else if (menuButtons.getCurrent() == "RESET") {
                    currentBeat = beat_;
                    mode = 0;
                }
                else if (menuButtons.getCurrent() == "QUIT") {
                    return 0;
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
                event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
                event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
                menuButtons.prev();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
                event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
                event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {
                menuButtons.next();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
                event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
                event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
                currentBeat -= 0.01;
                if (currentBeat < beat_ - 8)
                    currentBeat = beat_ - 8;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
                event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
                event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
                currentBeat += 0.01;
                if (currentBeat > beat_)
                    currentBeat = beat_;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
                event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7) {
                return -1;
            }
        }

        menuButtons.update(elapsedTime);
        fps.restart();
        for (auto& joueur : joueurs_) {
            joueur.update(elapsedTime, &arena_, currentBeat, false);
        }

        for (auto& totem : totems_) {
            totem.update(elapsedTime, &arena_, currentBeat, false);
        }

        for (auto& mech : mechanicList_) {
            mech->update(elapsedTime, currentBeat, em_);
        }

        arena_.update(elapsedTime);

        
        int res = client->updateFromServerPlayerPosition(joueurs_, checkpoint);
        if (res != 0)
            return res;


        window.clear(sf::Color(0x2A2431FF));
        renderText.clear(sf::Color::Transparent);
        renderText.setView(arena_.getView());

        arena_.draw(renderText);

        if (mode == 0) {
            for (int i = 0; i < mechanicList_.size(); i++) {
                mechanicList_[i]->draw(elapsedTime, renderText);
            }
        }
        if (mode == 1) {
            for (int i = 0; i < failed_.size(); i++) {
                mechanicList_[failed_[i]]->draw(elapsedTime, renderText);
            }
        }
        if (mode == 2) {
            for (int i = 0; i < mechanicList_.size(); i++) {
                if(mechanicList_[i]->getBeat() < beat_)
                    mechanicList_[i]->draw(elapsedTime, renderText);
            }
        }

        for (int i = 0; i < NB_MAX_TOTEM; i++) {
            totems_[i].draw(renderText);
        }

        for (int i = 0; i < NB_MAX_JOUEURS; i++) {
            joueurs_[i].draw(renderText);
        }

        renderText.display();
        sf::Sprite sp(renderText.getTexture());
        window.draw(sp);

        song_->drawProgress(window, currentBeat, 0);

        for (int i = 0; i < namesInfo.size(); i++) {
            if (joueurs_[i].getActive()) {
                window.draw(namesInfo[i]);
                window.draw(namesText[i]);
            }
        }

        menuButtons.draw(window);

        window.display();
    }

    return -1;
}

void RoomStatus::clear()
{
    for (int i = 0; i < mechanicList_.size(); i++)
        mechanicList_[i]->reset(0);

    failed_.clear();

    arena_.clear();
}

void RoomStatus::setup(RoomStatusData& data)
{
    for (int i = 0; i < data.playerActive.size(); i++) {
        joueurs_[i].setName(data.names[i]);
        joueurs_[i].setColor(data.playerColors[i]);
        joueurs_[i].setActive(data.playerActive[i]);
        joueurs_[i].setPosition(data.playerX[i], data.playerY[i]);
    }

    for (int i = 0; i < data.totemActive.size(); i++) {
        totems_[i].setColor(data.totemColors[i]);
        totems_[i].setActive(data.totemActive[i]);
        totems_[i].setPosition(data.totemX[i], data.totemY[i]);
        totems_[i].setTarget(sf::Vector2f(data.totemX[i], data.totemY[i]), 0, true);
    }

    for (int i = 0; i < data.failed.size(); i++) {
        failed_.emplace_back(data.failed[i]);
    }

    for (int i = 0; i < data.rl.size(); i++) {
        arena_.addRect(data.rl[i], data.rt[i], data.rw[i], data.rh[i]);
    }
    
    beat_ = data.beat;

    arena_.setZoom(data.zoom);
    arena_.setRotation(data.rotation);
    arena_.setTop(data.top);
    arena_.setLeft(data.left);
    arena_.setWidth(data.width);
    arena_.setHeight(data.height);
}
