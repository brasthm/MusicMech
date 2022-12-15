//
// Created by cyril on 16/05/2022.
//

#include <iostream>
#include <cmath>

#include "Game.h"
#include "main.h"
#include "RoomStatus.h"

#include "System/Song.h"

#include "System/RessourceLoader.h"
#include "Mechanics/Mechanic.h"

#include "Graphics/LoadingScreen.h"
#include "Graphics/RingShape.h"
#include "Graphics/ButtonGroup.h"
#include "System/RessourceLoader.h"

#include "Mechanics/EndMap.h"

#include "MapsCode.h"


#include <cmath>
#include <future>

Game::Game() {
    online_ = false;
}

void Game::run(sf::RenderWindow &window, Client* client, bool creator) {
    totems_.clear();
    em_.clear();

    for(int i = 0; i < NB_MAX_TOTEM; i++) {
        totems_.emplace_back();
    }

    for(int i = 0; i < NB_MAX_JOUEURS; i++) {
        em_.addPlayer(std::addressof(joueurs_[i]));
    }
    for(int i = 0; i < NB_MAX_TOTEM; i++) {
        em_.addTotem(std::addressof(totems_[i]));
    }

    em_.addArena(&arena_);


    bool godmode = false, serverTrace = false;

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


    sf::Clock fps, send, ping;

    int current = client->getPlayerIndex();

    sf::Text fps_text, beat_text, beat_serv_text, ping_text ,godmode_text, position_text, position_serv_text, section_text, death_text;

    fps_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    fps_text.setCharacterSize(18);

    beat_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    beat_text.setCharacterSize(18);
    beat_text.setPosition(0, 20);

    beat_serv_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    beat_serv_text.setCharacterSize(18);
    beat_serv_text.setPosition(0,20*2);

    beat_serv_text.setString("Server beat: 0 (+0)");

    position_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    position_text.setCharacterSize(18);
    position_text.setPosition(0, 20 * 3);

    position_text.setString("Position: 0");

    position_serv_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    position_serv_text.setCharacterSize(18);
    position_serv_text.setPosition(0, 20 * 4);

    position_serv_text.setString("Server position: 0 (+0)");

    ping_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    ping_text.setCharacterSize(18);
    ping_text.setPosition(0, 20 * 5);

    ping_text.setString("Ping: 0");

    godmode_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    godmode_text.setCharacterSize(18);
    godmode_text.setPosition(0, 20 * 6);
    godmode_text.setString(GOD_MODE ? "Godmode: true" : "Godmode : false");

   section_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
   section_text.setCharacterSize(18);
   section_text.setPosition(0, 20 * 7);




    joueurs_[current].setActive(true);
    joueurs_[current].setControlledByPlayer(true);


    std::cout << "Current : " << current << std::endl;

    sf::Texture texture;

    sf::Sprite clear;
    clear.setTexture(RessourceLoader::getTexture("Images/clear.png"));

    IFloat xText(0);

    bool cleared = false;

    sf::Clock displayTest, endTimer_;

    music_.play();

    bool exit = false, interupted = false, sent = false, failed = false, resume = false, paused = false, refreshPing = false, restartSent = false;
    bool drawDebug = false, gameOver = false;
    std::pair<float, float> checkpoint;


    sf::RectangleShape fond;
    fond.setSize({ WIDOW_WIDTH, WIDOW_HEIGHT });
    fond.setFillColor(sf::Color(0x000000CC));

    ButtonGroup pauseButtons, gameOverButtons;

    pauseButtons.addButton(Button("RESUME", "Resume", 0xa5c882ff, WIDOW_WIDTH / 2.f - 125, 450, 250, 70));
    pauseButtons.addButton(Button("QUIT", "Quit", 0xff6392ff, WIDOW_WIDTH / 2.f - 75, 580, 150, 70));

    if (creator) {
        gameOverButtons.addButton(Button("RETRY", "Retry", 0xa5c882ff, WIDOW_WIDTH / 2.f - 125, 580, 250, 70));
        gameOverButtons.addButton(Button("RECAP", "Death recap", 0xf7dd72ff, WIDOW_WIDTH / 2.f - 150, 710, 300, 70));
        gameOverButtons.addButton(Button("QUIT", "Quit", 0xff6392ff, WIDOW_WIDTH / 2.f - 75, 840, 150, 70));
    }
    else {
        gameOverButtons.addButton(Button("RECAP", "Death recap", 0xf7dd72ff, WIDOW_WIDTH / 2.f - 150, 580, 300, 70));
        gameOverButtons.addButton(Button("QUIT", "Quit", 0xff6392ff, WIDOW_WIDTH / 2.f - 75, 710, 150, 70));
    }
    

    sf::Text pauseText, gameOverText, gameOverInfo;

    LoadingScreen loading;

    std::future<bool> waiting;

   pauseText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
   pauseText.setString("PAUSE");
   pauseText.setCharacterSize(108);
   pauseText.setPosition(WIDOW_WIDTH/2.f - pauseText.getGlobalBounds().width/2.f, 250);
   pauseText.setFillColor(sf::Color::White);

   gameOverText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
   gameOverText.setString("FAIL");
   gameOverText.setCharacterSize(108);
   gameOverText.setPosition(WIDOW_WIDTH / 2.f - pauseText.getGlobalBounds().width / 2.f, 250);
   gameOverText.setFillColor(sf::Color::White);


   gameOverInfo.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
   gameOverInfo.setCharacterSize(50);
   gameOverInfo.setFillColor(sf::Color::White);

   death_text.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
   death_text.setCharacterSize(30);
   death_text.setPosition(10, 10);


   int death = 0;

   for (int i = 0; i < joueurs_.size(); i++) {
       joueurs_[i].showPlate();
   }


   int currentControled = 0;
   float gameOverBeat, gameOverSection;

   //client->requestPing();

   sf::RenderTexture renderText;
   renderText.create(WIDOW_WIDTH, WIDOW_HEIGHT);

    window.setKeyRepeatEnabled(false);
    while (!exit)
    {
        int res = -1;
        sf::Time currentPos = music_.getPlayingOffset();
        float currentBeat_float = song_.getCumulativeNBeats(currentPos.asMilliseconds());
        float currentSection = song_.getCheckpoint(currentBeat_float);
        

        sf::Time elapsedTime = fps.getElapsedTime();
        fps.restart();

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed && !interupted) {
                client->sendEndGame();
                interupted = true;
            }
            
            if (!loading.getActive()) {
                if (failed) {
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
                        event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0) {
                        if (gameOverButtons.getCurrent() == "RETRY") {
                            if (!restartSent) {
                                client->sendResumeGame();
                                restartSent = true;
                            }
                        }
                        else if (gameOverButtons.getCurrent() == "RECAP") {
                            RoomStatus roomStatus(&song_, &mechanicList_);
                            client->requestRoomStatus(&roomStatus, roomStatus.getEntityManager());

                            res = roomStatus.run(window, client, em_);
                        }
                        else if (gameOverButtons.getCurrent() == "QUIT") {
                            client->sendEndGame();
                            interupted = true;
                        }
                    }

                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
                        event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
                        event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
                        gameOverButtons.prev();
                    }
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
                        event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
                        event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {
                        gameOverButtons.next();
                    }
                }
                else {
                    if (paused) {
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape ||
                            event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 1 ||
                            event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7) {
                            paused = false;
                        }
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return ||
                            event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 0) {
                            if (pauseButtons.getCurrent() == "RESUME") {
                                paused = false;
                            }
                            else if (pauseButtons.getCurrent() == "QUIT") {
                                client->sendEndGame();
                                interupted = true;
                            }
                        }

                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up ||
                            event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == -100 ||
                            event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100) {
                            pauseButtons.prev();
                        }
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down ||
                            event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::Y && event.joystickMove.position == 100 ||
                            event.type == sf::Event::JoystickMoved && event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100) {
                            pauseButtons.next();
                        }
                    }
                    else {
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && !interupted ||
                            event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 7 && !interupted) {
                            paused = !paused;
                        }
                    }
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::F1) {
                        drawDebug = !drawDebug;
                    }
                    if (event.key.code == sf::Keyboard::F2) {
                        serverTrace = !serverTrace;
                    }
                    /*if (event.key.code == sf::Keyboard::F3) {
                        currentControled++;
                        currentControled = currentControled % joueurs_.size();
                        for(int i = 0; i < joueurs_.size(); i++)
                            joueurs_[i].setControlledByPlayer(i == currentControled);
                    }
                    if (event.key.code == sf::Keyboard::F8) {
                        auto checkpoint = song_.getNextCheckpoint(currentBeat_float);
                        music_.setPlayingOffset(sf::seconds(checkpoint.first + 5));
                    }
                    if (event.key.code == sf::Keyboard::F7) {
                        auto checkpoint = song_.getCurrentCheckpoint(currentBeat_float);
                        music_.setPlayingOffset(sf::seconds(checkpoint.first));
                    }*/
                }
            }
        }

        client->keepAlive();

        // CLEARED
        if (!cleared) {
            cleared = em_.getCleared();
            if (cleared) {
                endTimer_.restart();
                xText.set(768, 0.3);
            }
        }


        

        fps_text.setString("FPS: " + std::to_string(1.f / elapsedTime.asSeconds()));
        beat_text.setString("Beat: " + std::to_string(currentBeat_float));
        position_text.setString("Position: " + std::to_string(currentPos.asSeconds()));
        section_text.setString("Section : " + std::to_string(currentSection));

        loading.update(elapsedTime);

        // RESTART
        if (waiting.valid() && waiting.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {

            if (waiting.get()) {
                sent = false;
                failed = false;
                restartSent = false;
                gameOver = false;
                for (int i = 0; i < joueurs_.size(); i++) {
                    joueurs_[i].showPlate();
                }
                music_.play();
            }

            waiting = std::future<bool>();
            loading.stop();
        }

        bool newfailed = false;

        
        if (!waiting.valid()) {

            // CLEARED
            if (cleared && endTimer_.getElapsedTime() > sf::seconds(5)) {
                if (creator) {
                    client->sendEndGame();
                    interupted = true;
                }
            }

            // UPDATE
            if (!failed) {
                for (auto& joueur : joueurs_) {
                    joueur.update(elapsedTime, &arena_, currentBeat_float, window.hasFocus() && !paused);
                }

                for (auto& totem : totems_) {
                    totem.update(elapsedTime, &arena_, currentBeat_float);
                }

                for (auto& mech : mechanicList_) {
                    mech->update(elapsedTime, currentBeat_float, em_);
                    if (!GOD_MODE)
                        newfailed = newfailed || mech->isFailed();
                    else
                        mech->negateFailed();
                }

                if (send.getElapsedTime().asMilliseconds() > CLIENT_TICK_MS) {
                    client->sendPlayerData((int)joueurs_[current].getPosX(), (int)joueurs_[current].getPosY());
                    send.restart();
                }

                arena_.update(elapsedTime);
            }

            // SEND PING
            if (ping.getElapsedTime().asSeconds() > 0.1) {
                ping.restart();

                client->requestPing();
            }

            // MONITOR SERVER
            if (!exit && res == -1) {
                res = client->updateFromServerPlayerPosition(joueurs_, checkpoint, em_);
            }


            exit = res == 1;
            if(!newfailed) newfailed = res == 2;
            if (failed)    resume = res == 3;
            refreshPing = res == 4;

            // PAUSE UPDATE
            if (paused) {
                pauseButtons.update(elapsedTime);
            }

            if (failed) {
                gameOverButtons.update(elapsedTime);
            }

            // PING RECIEVED
            if (refreshPing) {
                refreshPing = false;

                float serverbeat = client->getServerBeat();
                float off = currentBeat_float - serverbeat;
                float serverpos = client->getPosition();
                float offpos = (currentPos.asSeconds() - serverpos) * 1000;

                ping_text.setString("Ping: " + std::to_string(client->getPing()));
                beat_serv_text.setString("Server beat: " + std::to_string(serverbeat) + " (" + std::to_string(off) + ")");
                godmode_text.setString(client->getGodMode() ? "Godmode: true" : "Godmode : false");
                position_serv_text.setString("Server position: " + std::to_string(serverpos) + "(" + std::to_string((int)offpos) + "ms)");
            }

            // RESTART RECIEVED
            if (resume) {
                loading.start("Starting");
                waiting = std::async(std::launch::async, &Client::waitToStart, client);

                resume = false;
            }
        }


        window.clear(sf::Color(0x2A2431FF));
        renderText.clear(sf::Color::Transparent);
        renderText.setView(arena_.getView());

        // DRAW GAME
        if(!failed) {
            arena_.draw(renderText);

            for(int i = 0; i < mechanicList_.size(); i++) {
                mechanicList_[i]->draw(elapsedTime, renderText);
            }

            for(int  i = 0; i < NB_MAX_TOTEM; i++) {
                totems_[i].draw(renderText);
            }

            for(int i = 0; i < NB_MAX_JOUEURS; i++) {
                joueurs_[i].draw(renderText, serverTrace);
            }

            renderText.display();
            sf::Sprite sp(renderText.getTexture());
            window.draw(sp);

            song_.drawProgress(window, currentBeat_float, currentSection);

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
                        window.draw(sp);

                        sf::Text txt;
                        txt.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
                        txt.setCharacterSize(30);
                        txt.setString(std::to_string(int(debuffsInfo[j].end - currentBeat_float)));
                        txt.setFillColor(sf::Color::Black);
                        txt.setPosition(size.width + 10 + j * 55 + 2, size.top + 16);
                        window.draw(txt);
                    }
                }
            }
        }
        // DRAW GAMEOVER 
        else {
            sf::RectangleShape screen;
            screen.setTexture(&texture);
            screen.setSize({(float)texture.getSize().x, (float)texture.getSize().y});
            window.draw(screen);

            window.draw(fond);
            gameOverButtons.draw(window);
            song_.drawSection(window, gameOverBeat, gameOverSection);
            window.draw(gameOverText);
            window.draw(gameOverInfo);
            window.draw(death_text);
        }

        // FAILED
        if(!failed) failed = !godmode && newfailed;
        if(failed) {
            // FIRST FRAME
            if(!sent) {
                music_.pause();
                std::cout << "failed" << std::endl;
                sent = true;
                gameOver = true;

                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);

                std::cout << checkpoint.first << " " << checkpoint.second << std::endl;

                reset(checkpoint.second);
                music_.setPlayingOffset(sf::seconds(checkpoint.first));

                gameOverBeat = currentBeat_float - 0.5;
                gameOverSection = song_.getCheckpoint(checkpoint.second + 1);

                gameOverText.setString("FAIL - Phase " + std::to_string((int)gameOverSection +1) + "/" + std::to_string(song_.getMaxCheckpoint()));
                gameOverText.setPosition(WIDOW_WIDTH / 2.f - gameOverText.getGlobalBounds().width / 2.f, 100);

                int pourcentage = song_.getSectionPourcentage(gameOverBeat, gameOverSection);
                gameOverInfo.setString("Current phase: " + std::to_string(pourcentage) + "%");
                gameOverInfo.setPosition(WIDOW_WIDTH / 2.f - gameOverInfo.getGlobalBounds().width / 2.f, 400);

                death++;
                death_text.setString("Death counter: " + std::to_string(death));

            }

            /*if (!restartSent && !exit && !interupted) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    client->sendResumeGame();
                    restartSent = true;
                }
            }*/
            
        }


        // DRAW CLEAR
        if (cleared) {
            xText.update(elapsedTime);
            clear.setPosition(xText.get(), 300);
            window.draw(clear);
        }

        
        // DRAW PAUSE

        if (paused) {
            window.draw(fond);
            pauseButtons.draw(window);
            window.draw(pauseText);
        }

        loading.draw(window);

        // DRAW LOADING
        if (drawDebug) {
            window.draw(fps_text);
            window.draw(beat_text);
            window.draw(godmode_text);
            window.draw(beat_serv_text);
            window.draw(ping_text);
            window.draw(position_serv_text);
            window.draw(position_text);
            window.draw(section_text);
        }

        window.display();
    }

    music_.stop();
}

void Game::load() {
}

void Game::loadFromFile(const std::string& path)
{
    for (int i = 0; i < mechanicList_.size(); i++) {
        delete mechanicList_[i];
    }

    mechanicList_.clear();
    arena_.clear();

    song_.load(path, &music_, mechanicList_, &arena_);
    music_.setVolume(10);


    std::cout << "Mechanics number : " << mechanicList_.size() << std::endl;

   //music_.setPlayingOffset(sf::seconds(167));

    std::sort(mechanicList_.begin(), mechanicList_.end(),
        [](Mechanic* m1, Mechanic* m2) {return *m1 < *m2; });

    bool found = false;
    float beat;
    for (int i = 0; i < mechanicList_.size(); i++) {
        if (EndMap* em = dynamic_cast<EndMap*>(mechanicList_[i])) {
            beat = em->getBeat();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Warning : no EndMap" << std::endl;
        beat = song_.getCumulativeNBeats(music_.getDuration().asMilliseconds());
    }

    std::cout << "EndMap : " << beat << std::endl;
    song_.setEndBeat(beat);
}

void Game::loadFromCode(const std::string& id, const std::string& path)
{
    em_.deleteSequences();

    song_.load(path, &music_, mechanicList_, &arena_);
    music_.setVolume(10);

    mechanicList_.clear();

    getMechsFromCode(id, mechanicList_, song_, music_, em_);

    std::cout << "Mechanics number : " << mechanicList_.size() << std::endl;

    //music_.setPlayingOffset(sf::seconds(221));

    std::sort(mechanicList_.begin(), mechanicList_.end(),
        [](Mechanic* m1, Mechanic* m2) {return *m1 < *m2; });

    bool found = false;
    float beat;
    for (int i = 0; i < mechanicList_.size(); i++) {
        if (EndMap* em = dynamic_cast<EndMap*>(mechanicList_[i])) {
            beat = em->getBeat();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Warning : no EndMap" << std::endl;
        beat = song_.getCumulativeNBeats(music_.getDuration().asMilliseconds());
    }

    std::cout << "EndMap : " << beat << std::endl;
    song_.setEndBeat(beat);
}



Game::~Game() {
    for(int i = 0; i < mechanicList_.size(); i++) {
        delete mechanicList_[i];
    }
}

void Game::reset(float beat) {
    for(auto & i : mechanicList_) {
        i->reset(beat);
    }

    for(auto & totem:totems_) {
        totem.setActive(false);
    }

    for(auto & joueur:joueurs_) {
        joueur.reset();
    }
}

void Game::clearPlayer()
{
    joueurs_.clear();
}

void Game::addPlayer(std::string name ,sf::Uint32 color)
{
    joueurs_.emplace_back();
    if (name != "") {
        joueurs_.back().setName(name);
        joueurs_.back().setColor(color);
    }
    joueurs_.back().computePlate();
}

EntityManager& Game::getEntityManager()
{
    return em_;
}

void Game::save(const std::string &filename) {
    song_.save(filename, mechanicList_, arena_);
}




