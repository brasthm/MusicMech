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
        debuffsNumbers_.emplace_back(0);
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

    for (int i = 0; i < mechanicList_.size(); i++) {
        mechanicList_[i]->reset(0);
        mechanicList_[i]->setPause(true);
    }

    failed_.clear();
    arena_.clear();

    em_.addArena(&arena_);

    song_ = song;
}

RoomStatus::~RoomStatus()
{
    for (int i = 0; i < mechanicList_.size(); i++) {
        delete mechanicList_[i];
    }
}

int RoomStatus::run(sf::RenderWindow& window, Client* client, EntityManager &em)
{
    bool exit = false;

    float currentBeat = beat_;

    int selectDebuffsRow = 0, selectDebuffsCol = 0;
    bool inspectDebuffs = false;

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
    menuButtons.addButton(Button("QUIT",        "Back",             0xff6392ff, 0, 380, 90, 50));


    sf::RectangleShape debuffInfo;
    sf::Text textDebuffInfo, textDebuffDescription, textDebuffDuration;
    sf::Sprite debuffIconInfo;

    debuffInfo.setSize({800.f, 300.f});
    debuffInfo.setFillColor(sf::Color(200, 200, 200, 255));
    debuffInfo.setPosition(WIDOW_WIDTH - 800.f, WIDOW_HEIGHT - 300);

    auto box = debuffInfo.getGlobalBounds();

    textDebuffInfo.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
    textDebuffInfo.setCharacterSize(50);
    textDebuffInfo.setFillColor(sf::Color::Black);
    textDebuffInfo.setPosition(box.left + 130, box.top + 30);

    textDebuffDescription.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    textDebuffDescription.setCharacterSize(28);
    textDebuffDescription.setFillColor(sf::Color::Black);
    textDebuffDescription.setPosition(box.left + 10, box.top + 140);

    textDebuffDuration.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    textDebuffDuration.setCharacterSize(28);
    textDebuffDuration.setFillColor(sf::Color::Black);
    textDebuffDuration.setPosition(box.left + 10, WIDOW_HEIGHT - 40);

    std::pair<float, float> checkpoint;

    sf::RenderTexture renderText;
    renderText.create(WIDOW_WIDTH, WIDOW_HEIGHT);
    for (int i = 0; i < mechanicList_.size(); i++) {
        mechanicList_[i]->setFailed(false);
    }
    for (int j = 0; j < failed_.size(); j++) {
        mechanicList_[failed_[j]]->setFailed(true);
    }
    

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
                else if (menuButtons.getCurrent() == "DEBUFF") {
                    if (!inspectDebuffs) {
                        for (int i = 0; i < debuffsNumbers_.size(); i++) {
                            if (debuffsNumbers_[i] != 0) {
                                inspectDebuffs = true;
                                selectDebuffsRow = i;
                                selectDebuffsCol = 0;
                                break;
                            }
                        }
                    }
                }
                else if (menuButtons.getCurrent() == "QUIT") {
                    return 0;
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
                event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7) {
                if (inspectDebuffs)
                    inspectDebuffs = false;
                else
                    return -1;
            }

            if (inspectDebuffs) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
                    event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
                    event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
                    do {
                        selectDebuffsRow--;
                        if (selectDebuffsRow < 0)
                            selectDebuffsRow = debuffsNumbers_.size() - 1;
                    } while (debuffsNumbers_[selectDebuffsRow] == 0);

                    if (selectDebuffsCol >= debuffsNumbers_[selectDebuffsRow])
                        selectDebuffsCol = 0;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
                    event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
                    event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {
                    do {
                        selectDebuffsRow++;
                        if (selectDebuffsRow >= debuffsNumbers_.size())
                            selectDebuffsRow = 0;
                    }
                    while (debuffsNumbers_[selectDebuffsRow] == 0);

                    if (selectDebuffsCol >= debuffsNumbers_[selectDebuffsRow])
                        selectDebuffsCol = 0;

                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
                    event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == -100 ||
                    event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100) {
                    selectDebuffsCol--;
                    if (selectDebuffsCol < 0)
                        selectDebuffsCol = debuffsNumbers_[selectDebuffsRow] - 1;

                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right ||
                    event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::X && event.joystickMove.position == 100 ||
                    event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100) {
                    selectDebuffsCol++;
                    if (selectDebuffsCol >= debuffsNumbers_[selectDebuffsRow])
                        selectDebuffsCol = 0;
                }
            }
            else {
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
            }
            
            /*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left ||
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
            }*/
        }

        client->keepAlive();

        menuButtons.update(elapsedTime);
        fps.restart();
        for (auto& joueur : joueurs_) {
            //joueur.update(elapsedTime, &arena_, currentBeat, false);
        }

        for (auto& totem : totems_) {
            //totem.update(elapsedTime, &arena_, currentBeat, false);
        }

        for (auto& mech : mechanicList_) {
            //mech->update(elapsedTime, currentBeat, em_);
        }

        arena_.update(elapsedTime);

        
        int res = client->updateFromServerPlayerPosition(joueurs_, checkpoint, em);
        if (res == 1 || res == 2 || res == 3)
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
            joueurs_[i].draw(renderText , false);
        }

        renderText.display();
        sf::Sprite sp(renderText.getTexture());
        window.draw(sp);

        song_->drawProgress(window, currentBeat, 0);

        if (inspectDebuffs) {
            std::vector<DebuffInfo> debuffsInfo;
            joueurs_[selectDebuffsRow].getDebuffs(debuffsInfo);
            textDebuffInfo.setString(debuffsInfo[selectDebuffsCol].name);
            textDebuffDescription.setString("");

            auto mots = Utils::split(debuffsInfo[selectDebuffsCol].desc, ' ');
            std::string resText = mots[0];

            for (int i = 1; i < mots.size(); i++) {
                std::string test = resText + " " + mots[i];
                textDebuffDescription.setString(test);
                auto b = textDebuffDescription.getGlobalBounds();
                if (b.left + b.width > WIDOW_WIDTH) {
                    resText += "\n" + mots[i];
                }
                else {
                    resText += " " + mots[i];
                }
            }

            textDebuffDescription.setString(resText);

            std::string duration = "Duration: " + std::to_string((int)(debuffsInfo[selectDebuffsCol].end - currentBeat));
            textDebuffDuration.setString(duration);

            sf::Sprite icon;
            icon.setTexture(RessourceLoader::getTexture(debuffsInfo[selectDebuffsCol].icon));
            icon.setScale(0.5, 0.5);
            icon.setPosition(box.left + 10, box.top + 10);


            window.draw(debuffInfo);
            window.draw(icon);
            window.draw(textDebuffInfo);
            window.draw(textDebuffDescription);
            window.draw(textDebuffDuration);


        }

        for (int i = 0; i < namesInfo.size(); i++) {
            if (joueurs_[i].getActive()) {
                window.draw(namesInfo[i]);
                window.draw(namesText[i]);

                std::vector<DebuffInfo> debuffsInfo;

                joueurs_[i].getDebuffs(debuffsInfo);

                auto size = namesInfo[i].getGlobalBounds();

                for (int j = 0; j < debuffsInfo.size(); j++) {
                    sf::Sprite sp;
                    sp.setTexture(RessourceLoader::getTexture(debuffsInfo[j].icon));
                    sp.setScale(0.25, 0.25);
                    sp.setPosition(size.width + 10 + j * 55, size.top - 2);
                    

                    sf::Text txt;
                    txt.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
                    txt.setCharacterSize(30);
                    txt.setString(std::to_string(int(debuffsInfo[j].end - currentBeat)));
                    txt.setFillColor(sf::Color::Black);
                    txt.setPosition(size.width + 10 + j * 55 + 2, size.top + 16);
                    

                    if (inspectDebuffs && i == selectDebuffsRow && j == selectDebuffsCol) {
                        sf::RectangleShape highlight;
                        auto size = sp.getGlobalBounds();
                        highlight.setFillColor(sf::Color::White);
                        highlight.setPosition(size.left - 5, size.top - 5);
                        highlight.setSize({ size.width + 10, size.height + 10 });
                        window.draw(highlight);
                    }

                    window.draw(sp);
                    window.draw(txt);
                }
            }
        }

        menuButtons.draw(window);

        window.display();
    }

    return -1;
}


void RoomStatus::addJoueur(int i, std::string& name, sf::Uint32 color, bool active, float x, float y)
{
    joueurs_[i].setName(name);
    joueurs_[i].setColor(color);
    joueurs_[i].setActive(active);
    joueurs_[i].setPosition(x, y);
    joueurs_[i].setServerPosition(x, y);
}

void RoomStatus::addTotem(int i, sf::Uint32 color, bool active, float x, float y)
{
    totems_[i].setColor(color);
    totems_[i].setActive(active);
    totems_[i].setPosition(x, y);
    totems_[i].setTarget(sf::Vector2f(x, y), 0, true);
}

void RoomStatus::addFailed(int i)
{
    failed_.emplace_back(i);
}

void RoomStatus::addArenaRect(float rl, float rt, float rw, float rh)
{
    arena_.addRect(rl, rt, rw, rh);
}

void RoomStatus::setBeat(float beat)
{
    beat_ = beat;
}

void RoomStatus::setArenaParameters(float zoom, float rotation, float left, float top, float width, float height)
{
    arena_.setZoom(zoom);
    arena_.setRotation(rotation);
    arena_.setTop(top);
    arena_.setLeft(left);
    arena_.setWidth(width);
    arena_.setHeight(height);
}

void RoomStatus::setMechPosition(int i, std::vector<sf::Vector2f>& positions)
{
    mechanicList_[i]->setTargetPos(positions);
}

void RoomStatus::setDebuffs(int i, DebuffType type, float end)
{
    joueurs_[i].applyDebuff(type, end);
    debuffsNumbers_[i]++;
}

EntityManager& RoomStatus::getEntityManager()
{
    return em_;
}


