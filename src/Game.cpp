//
// Created by cyril on 16/05/2022.
//

#include <iostream>
#include <cmath>

#include "Game.h"
#include "main.h"
#include "Graphics/RingShape.h"
#include "Graphics/ButtonGroup.h"
#include "System/RessourceLoader.h"
#include "Mechanics/Mechanic.h"
#include "Mechanics/ZoomArena.h"
#include "Mechanics/RotateArena.h"
#include "Mechanics/MoveArena.h"
#include "Mechanics/SnapArena.h"
#include "Mechanics/AddArena.h"
#include "Mechanics/RemoveArena.h"
#include "Mechanics/Donut.h"
#include "Mechanics/Spread.h"
#include "Mechanics/NopeZone.h"
#include "Mechanics/Cone.h"
#include "Mechanics/ActivateTotem.h"
#include "Mechanics/MoveEntity.h"
#include "Mechanics/Tether.h"
#include "Mechanics/ApplyDebuff.h"
#include "Mechanics/DisplayImage.h"
#include "Mechanics/ClearArenaa.h"
#include "Mechanics/EndMap.h"


#include "System/Song.h"


#include <cmath>

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


    bool godmode = false;


    sf::Clock fps, send, ping;

    int current = client->getPlayerIndex();

    sf::Text fps_text, beat_text, beat_serv_text, ping_text ,godmode_text;

    fps_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    fps_text.setCharacterSize(30);

    beat_text.setFont(RessourceLoader::getFont("Font/Roboto-Regular.ttf"));
    beat_text.setCharacterSize(30);

    beat_serv_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    beat_serv_text.setCharacterSize(18);
    beat_serv_text.setPosition(0,20*2);

    beat_serv_text.setString("Server position: 0 (+0)");

    ping_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    ping_text.setCharacterSize(18);
    ping_text.setPosition(0, 20 * 3);

    ping_text.setString("Ping: 0");

    godmode_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    godmode_text.setCharacterSize(18);
    godmode_text.setPosition(0, 20 * 4);


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

    bool exit = false, interupted = false, sent = false, failed = false, resume = false, paused = false, refreshPing = false;

    std::pair<float, float> checkpoint;


    sf::RectangleShape fond;
    fond.setSize({ WIDOW_WIDTH, WIDOW_HEIGHT });
    fond.setFillColor(sf::Color(0x000000CC));

    ButtonGroup pauseButtons;

    pauseButtons.addButton(Button("RESUME", "Resume", 0xa5c882ff, WIDOW_WIDTH / 2.f - 125, 450, 250, 70));
    pauseButtons.addButton(Button("QUIT", "Quit", 0xff6392ff, WIDOW_WIDTH / 2.f - 75, 580, 150, 70));

    sf::Text pauseText;

   pauseText.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
   pauseText.setString("PAUSE");
   pauseText.setCharacterSize(108);
   pauseText.setPosition(WIDOW_WIDTH/2.f - pauseText.getGlobalBounds().width/2.f, 250);
   pauseText.setFillColor(sf::Color::White);

   //client->requestPing();

    window.setKeyRepeatEnabled(false);
    while (!exit)
    {
        sf::Time currentPos = music_.getPlayingOffset();
        float currentBeat_float = song_.getCumulativeNBeats(currentPos.asMilliseconds());

        sf::Time elapsedTime = fps.getElapsedTime();
        fps.restart();

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed && !interupted) {
                client->sendEndGame();
                interupted = true;
            }
 
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
            
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::G) {
                    GOD_MODE = true;
                }
                if(event.key.code == sf::Keyboard::H) {
                    GOD_MODE = false;
                }
            }


        }

        if (!cleared) {
            cleared = em_.getCleared();
            if (cleared) {
                endTimer_.restart();
                xText.set(768, 0.3);
            }
        }
        if (cleared && endTimer_.getElapsedTime() > sf::seconds(5)) {
            if (creator) {
                client->sendEndGame();
                interupted = true;
            }
        }


        godmode_text.setString(GOD_MODE ? "Godmode: true":"Godmode : false");

        fps_text.setString("FPS: " + std::to_string(1.f / elapsedTime.asSeconds()));
        beat_text.setString("Position:" + std::to_string(currentBeat_float));

        bool newfailed = false;

        if(!failed) {
            for(auto & joueur : joueurs_) {
                joueur.update(elapsedTime, &arena_, currentBeat_float, window.hasFocus() && !paused);
            }

            for(auto & totem : totems_) {
                totem.update(elapsedTime, &arena_, currentBeat_float, window.hasFocus() && !paused);
            }

            for(auto & mech : mechanicList_) {
                mech->update(elapsedTime, currentBeat_float, em_);
                if (!GOD_MODE)
                    newfailed = newfailed || mech->isFailed();
                else
                    mech->negateFailed();
            }

            if(send.getElapsedTime().asMilliseconds() > CLIENT_TICK_MS) {
                client->sendPlayerData((int)joueurs_[current].getPosX(), (int)joueurs_[current].getPosY());
                send.restart();
            }

            arena_.update(elapsedTime);
        }

        if (ping.getElapsedTime().asSeconds() > 0.1) {
            ping.restart();

            client->requestPing();
        }

        if(!exit) {
            int res = client->updateFromServerPlayerPosition(joueurs_, checkpoint);
            exit = res == 1;
            newfailed = newfailed || res == 2;
            if(failed) resume = res == 3;
            refreshPing = res == 4;
        }

        if (paused) {
            pauseButtons.update(elapsedTime);
        }

        if (refreshPing) {
            refreshPing = false;

            float serverbeat = client->getServerBeat();
            float off = currentBeat_float - serverbeat;

            ping_text.setString("Ping: " + std::to_string(client->getPing()));
            beat_serv_text.setString("Server position: " + std::to_string(serverbeat) + " (" + std::to_string(off) +")");
        }

        window.clear(sf::Color(0x2A2431FF));

        if(!failed) {
            for(int i = 0; i < mechanicList_.size(); i++) {
                mechanicList_[i]->draw(elapsedTime, arena_.getRenderTexture());
            }

            for(int  i = 0; i < NB_MAX_TOTEM; i++) {
                totems_[i].draw(arena_.getRenderTexture());
            }

            for(int i = 0; i < NB_MAX_JOUEURS; i++) {
                joueurs_[i].draw(arena_.getRenderTexture());
            }

            arena_.draw(window);
        }
        else {
            sf::RectangleShape screen;
            screen.setTexture(&texture);
            screen.setSize({(float)texture.getSize().x, (float)texture.getSize().y});
            window.draw(screen);
        }

        if(!failed) failed = !godmode && newfailed;
        if(failed) {
            if(!sent) {
                music_.pause();
                std::cout << "failed" << std::endl;
                sent = true;

                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);

                std::cout << checkpoint.first << " " << checkpoint.second << std::endl;

                reset(checkpoint.second);
                music_.setPlayingOffset(sf::seconds(checkpoint.first));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                client->sendResumeGame();
                resume = true;
            }
        }

        if (cleared) {
            xText.update(elapsedTime);
            clear.setPosition(xText.get(), 300);
            window.draw(clear);
        }

        if(resume) {
            sent = false;
            failed = false;
            music_.play();
            resume = false;
        }

        if (paused) {
            window.draw(fond);
            pauseButtons.draw(window);
            window.draw(pauseText);
        }

        window.draw(fps_text);
        window.draw(beat_text);
        window.draw(godmode_text);
        window.draw(beat_serv_text);
        window.draw(ping_text);
        window.display();
    }

    music_.stop();
}

void Game::load() {
    song_.load(
            "Beatmaps/1772712 DECO 27 - Ai Kotoba IV feat. Hatsune Miku/[2P] DECO27 - Ai Kotoba IV feat. Hatsune Miku.mm",
            //"Beatmaps/1772712 DECO 27 - Ai Kotoba IV feat. Hatsune Miku/[TEST] DECO27 - Ai Kotoba IV feat. Hatsune Miku.mm",
            &music_,
            mechanicList_, &arena_);



    std::sort(mechanicList_.begin(), mechanicList_.end(),
              [] (Mechanic* m1, Mechanic* m2) {return *m1 < *m2;});
}

void Game::load(const std::string& path)
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

void Game::addPlayer(sf::Uint32 color)
{
    joueurs_.emplace_back();
    joueurs_.back().setColor(color);
}

void Game::save(const std::string &filename) {
    song_.save(filename, mechanicList_, arena_);
}




