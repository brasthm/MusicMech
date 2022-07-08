//
// Created by cyril on 16/05/2022.
//

#include <iostream>
#include <cmath>

#include "Game.h"
#include "main.h"
#include "Graphics/RingShape.h"
#include "System/RessourceLoader.h"
#include "Mechanics/Mechanic.h"
#include "Mechanics/Spread.h"
#include "Mechanics/Tether.h"
#include "Mechanics/ActivateTotem.h"
#include "Mechanics/MoveEntity.h"
#include "Mechanics/ApplyDebuff.h"

#include "System/Song.h"

Game::Game() : client_(nullptr){
    online_ = false;
}

Game::Game(Client *client) :client_(client) {
    online_ = true;
}


void Game::run(sf::RenderWindow &window, const std::string& roomID) {

    joueurs_.clear();
    totems_.clear();
    em_.clear();

    for(int i = 0; i < NB_MAX_JOUEURS; i++) {
        joueurs_.emplace_back();
    }

    for(int i = 0; i < NB_MAX_TOTEM; i++) {
        totems_.emplace_back();
    }

    for(int i = 0; i < NB_MAX_JOUEURS; i++) {
        em_.addPlayer(std::addressof(joueurs_[i]));
    }
    for(int i = 0; i < NB_MAX_TOTEM; i++) {
        em_.addTotem(std::addressof(totems_[i]));
    }


    bool godmode = false;


    sf::Clock fps, send;

    int current = client_->getIndex();

    sf::Text fps_text, beat_text, godmode_text;

    fps_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    fps_text.setCharacterSize(30);

    beat_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    beat_text.setCharacterSize(30);

    beat_text.setPosition(0,32);

    godmode_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    godmode_text.setCharacterSize(30);

    godmode_text.setPosition(0,32*2);


    joueurs_[current].setActive(true);
    joueurs_[current].setControlledByPlayer(true);


    std::cout << "Current : " << current << std::endl;

    sf::Texture texture;

    sf::Clock displayTest;

    song_.play();

    bool exit=false, interupted=false, sent=false, failed = false, resume=false;

    window.setKeyRepeatEnabled(false);
    while (!exit)
    {
        sf::Time currentPos = song_.getCurrentTime();
        float currentBeat_float = song_.getCumulativeNBeats(currentPos.asMilliseconds());

        sf::Time elapsedTime = fps.getElapsedTime();
        fps.restart();

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit=true;
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::G) {
                    godmode = true;
                }
                if(event.key.code == sf::Keyboard::H) {
                    godmode = false;
                }


                if(event.key.code == sf::Keyboard::V) {
                    auto checkpoint = song_.getPreviousCheckpoint(currentBeat_float);
                    reset(checkpoint.second);
                    song_.setTime(sf::seconds(checkpoint.first));
                }
                if(event.key.code == sf::Keyboard::B) {
                    auto checkpoint = song_.getCurrentCheckpoint(currentBeat_float);
                    reset(checkpoint.second);
                    song_.setTime(sf::seconds(checkpoint.first));
                }
                if(event.key.code == sf::Keyboard::N) {
                    auto checkpoint = song_.getNextCheckpoint(currentBeat_float);
                    reset(checkpoint.second);
                    song_.setTime(sf::seconds(checkpoint.first));
                }

            }
        }

        godmode_text.setString(godmode ? "Godmode : true":"Godmode : false");

        fps_text.setString(std::to_string(1.f/elapsedTime.asSeconds()));
        beat_text.setString(std::to_string(currentBeat_float));

        bool newfailed = false;

        if(!failed) {
            for(auto & joueur : joueurs_) {
                joueur.update(elapsedTime, currentBeat_float, window.hasFocus());
            }

            for(auto & totem : totems_) {
                totem.update(elapsedTime, currentBeat_float, window.hasFocus());
            }

            for(auto & mech : mechanicList_) {
                mech->update(elapsedTime, currentBeat_float, em_);
                newfailed = newfailed || mech->isFailed();
            }

            if(send.getElapsedTime().asMilliseconds() > CLIENT_TICK_MS) {
                client_->sendPlayerData((int)joueurs_[current].getPosX(), (int)joueurs_[current].getPosY());
                send.restart();
            }
        }

        if(!exit) {
            int res = client_->updateFromServerPlayerPosition(joueurs_);
            interupted = res == 1;
            newfailed = newfailed || res == 2;
            if(failed) resume = resume || res == 3;
            exit = interupted;
        }

        window.clear(sf::Color(0x2A2431FF));

        if(!failed) {
            for(int i = 0; i < mechanicList_.size(); i++) {
                mechanicList_[i]->draw(elapsedTime, window);
            }

            for(int  i = 0; i < NB_MAX_TOTEM; i++) {
                totems_[i].draw(window);
            }

            for(int i = 0; i < NB_MAX_JOUEURS; i++) {
                joueurs_[i].draw(window);
            }
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
                song_.pause();
                std::cout << "failed" << std::endl;
                client_->sendPauseGame(roomID);
                sent = true;

                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);


                auto checkpoint = song_.getCurrentCheckpoint(currentBeat_float);
                std::cout << checkpoint.first << " " << checkpoint.second << std::endl;

                reset(checkpoint.second);
                song_.setTime(sf::seconds(checkpoint.first));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                client_->sendResumeGame(roomID);
                resume = true;
            }
        }

        if(resume) {
            sent = false;
            failed = false;
            song_.play();
            resume = false;
        }

        window.draw(fps_text);
        window.draw(beat_text);
        window.draw(godmode_text);
        window.display();
    }

    if(!interupted)
        client_->sendEndGame(roomID);

    load();

}

void Game::load() {
    song_.load(
            "Beatmaps/1772712 DECO 27 - Ai Kotoba IV feat. Hatsune Miku/DECO27 - Ai Kotoba IV feat. Hatsune Miku ([Hatsune Miku]) [Daisuki].osu",
            mechanicList_);
    for (int i = 0; i < mechanicList_.size(); i++) {
        delete mechanicList_[i];
    }
    mechanicList_.clear();

    song_.resetCheckpoints();
    song_.addCheckpoint(0,0);
    song_.addCheckpoint(18,48);
    song_.addCheckpoint(30,78);
    song_.addCheckpoint(44,112);
    song_.addCheckpoint(58,140);
    song_.addCheckpoint(89,212);
    song_.addCheckpoint(104,248);
    song_.addCheckpoint(120,280);
    song_.addCheckpoint(133,308);
    song_.addCheckpoint(146,344);
    song_.addCheckpoint(173,412);


    mechanicList_.emplace_back(new Tether(15,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 4, false, false));

    // INTRO
    for(int ii = 0; ii < 28; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(16+i+0.5f, 100, 1, 4,
                                              Target(TARGET_POS,
                                                     {500.f + 350.f*std::cos(2.f*i*PI/16.f -PI/4),
                                                      500.f + 350.f*std::sin(2.f*i*PI/16.f -PI/4)})));
        mechanicList_.emplace_back(new Spread(16+i+0.5f, 100, 1, 4,
                                              Target(TARGET_POS,
                                                     {500.f + 350.f*std::cos(PI+2.f*i*PI/16.f - PI/4),
                                                      500.f + 350.f*std::sin(PI+2.f*i*PI/16.f - PI/4)})));

    }

    mechanicList_.emplace_back(new Spread(44.5f, 100, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 350.f*std::cos(2.f*28*PI/16.f -PI/4),
                                                  500.f + 350.f*std::sin(2.f*28*PI/16.f -PI/4)})));
    mechanicList_.emplace_back(new Spread(44.4f, 100, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 350.f*std::cos(PI+2.f*28*PI/16.f - PI/4),
                                                  500.f + 350.f*std::sin(PI+2.f*28*PI/16.f - PI/4)})));

    mechanicList_.emplace_back(new Spread(45.5f, 100, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 300.f*std::cos(2.f*28*PI/16.f -PI/4),
                                                  500.f + 300.f*std::sin(2.f*28*PI/16.f -PI/4)})));
    mechanicList_.emplace_back(new Spread(45.5f, 100, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 250.f*std::cos(PI+2.f*28*PI/16.f - PI/4),
                                                  500.f + 250.f*std::sin(PI+2.f*28*PI/16.f - PI/4)})));

    mechanicList_.emplace_back(new Spread(46.5f, 100, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 200.f*std::cos(2.f*28*PI/16.f -PI/4),
                                                  500.f + 200.f*std::sin(2.f*28*PI/16.f -PI/4)})));
    mechanicList_.emplace_back(new Spread(46.5f, 100, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 200.f*std::cos(PI+2.f*28*PI/16.f - PI/4),
                                                  500.f + 200.f*std::sin(PI+2.f*28*PI/16.f - PI/4)})));

    mechanicList_.emplace_back(new Spread(47.5f, 100, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 150.f*std::cos(2.f*28*PI/16.f -PI/4),
                                                  500.f + 150.f*std::sin(2.f*28*PI/16.f -PI/4)})));
    mechanicList_.emplace_back(new Spread(47.5f, 100, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 150.f*std::cos(PI+2.f*28*PI/16.f - PI/4),
                                                  500.f + 150.f*std::sin(PI+2.f*28*PI/16.f - PI/4)})));


    // COUPLET 1

    mechanicList_.emplace_back(new Spread(48, 200, 2, 8,
                                          Target(TARGET_POS,{500.f,500.f})));

    mechanicList_.emplace_back(new Tether(49.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 4, false, false));

    mechanicList_.emplace_back(new Spread(51, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(51.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(52, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(52.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(53, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(53.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(54, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(55, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanicList_.emplace_back(new Spread(51, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(51.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(52, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(52.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(53, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(53.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(54, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(55, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));




    mechanicList_.emplace_back(new Spread(56, 200, 2, 8,
                                          Target(TARGET_POS,{500.f,500.f})));

    mechanicList_.emplace_back(new Tether(57.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 4, false, false));

    mechanicList_.emplace_back(new Spread(59, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(59.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(60, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(60.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanicList_.emplace_back(new Spread(61.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(62, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(63, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanicList_.emplace_back(new Spread(59, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(59.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(60, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(60.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(61.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(62, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(63, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    mechanicList_.emplace_back(new Spread(64, 200, 2, 8,
                                          Target(TARGET_POS,{500.f,500.f})));

    mechanicList_.emplace_back(new Tether(65.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 4, false, false));

    mechanicList_.emplace_back(new Spread(67, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(67.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(68, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(68.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(69, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(69.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(70, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(71, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanicList_.emplace_back(new Spread(67, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(67.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(68, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(68.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(69, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(69.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(70, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(71, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    mechanicList_.emplace_back(new Spread(72, 200, 2, 8,
                                          Target(TARGET_POS,{500.f,500.f})));

    mechanicList_.emplace_back(new Tether(73.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 4, false, false));

    mechanicList_.emplace_back(new Spread(75, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(75.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanicList_.emplace_back(new Spread(75, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(75.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));


    // COUPLET 2

    mechanicList_.emplace_back(new Tether(88,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          500, 12, true, true));

    for(int i = 0; i < 4; i++) {
        mechanicList_.emplace_back(new Spread(80 + 2*i, 150, 1, 4,
                                              Target(TARGET_POS, {150.f +87.5f*2*i, 250})));
        mechanicList_.emplace_back(new Spread(80 + 2*i, 150, 1, 4,
                                              Target(TARGET_POS, {150.f +87.5f*2*i, 750})));
    }


    mechanicList_.emplace_back(new Tether(96,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          500, 8, false, true));

    for(int i = 0; i < 4; i++) {
        mechanicList_.emplace_back(new Spread(88 + 2*i, 150, 1, 4,
                                              Target(TARGET_POS, {850.f -87.5f*2*i, 250})));
        mechanicList_.emplace_back(new Spread(88 + 2*i, 150, 1, 4,
                                              Target(TARGET_POS, {850.f -87.5f*2*i, 750})));
    }


    mechanicList_.emplace_back(new Tether(104,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          500, 8, true, true));

    for(int i = 0; i < 4; i++) {
        mechanicList_.emplace_back(new Spread(96 + 2*i, 150, 1, 4,
                                              Target(TARGET_POS, {150.f +87.5f*2*i, 250})));
        mechanicList_.emplace_back(new Spread(96 + 2*i, 150, 1, 4,
                                              Target(TARGET_POS, {150.f +87.5f*2*i, 750})));
    }


    mechanicList_.emplace_back(new Tether(112,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          500, 8, false, true));

    for(int i = 0; i < 4; i++) {
        mechanicList_.emplace_back(new Spread(104 + 2*i, 150, 1, 4,
                                              Target(TARGET_POS, {850.f -87.5f*2*i, 250})));
        mechanicList_.emplace_back(new Spread(104 + 2*i, 150, 1, 4,
                                              Target(TARGET_POS, {850.f -87.5f*2*i, 750})));
    }


    // COUPLET 3

    for(int ii = 0; ii < 4; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(112 + 4*i, 300, 1, 4,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanicList_.emplace_back(new Spread(114 + 4*i, 300, 0, 2,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanicList_.emplace_back(new Spread(112 + 4*i, 300, 1, 4,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanicList_.emplace_back(new Spread(114 + 4*i, 300, 0, 2,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    }

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(128 + 2*i, 100, 1, 2,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanicList_.emplace_back(new Spread(129 + 2*i, 100, 0, 1,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanicList_.emplace_back(new Spread(128 + 2*i, 100, 1, 2,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanicList_.emplace_back(new Spread(129 + 2*i, 100, 0, 1,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    }


    // REFRAIN 1

    mechanicList_.emplace_back(new MoveEntity(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                              Target(TARGET_POS, {500, 50}),-1, true));
    mechanicList_.emplace_back(new ActivateTotem(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));

    mechanicList_.emplace_back(new MoveEntity(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                              Target(TARGET_POS, {500, 950}),-1, true));
    mechanicList_.emplace_back(new ActivateTotem(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));

    mechanicList_.emplace_back(new Tether(144,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(144,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          300, 4, true, false));


    mechanicList_.emplace_back(new Tether(148,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(152,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(156,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(148,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(152,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(156,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          800, 4, false, false));



    for(int ii = 0; ii < 13; ii++) {
        auto i = static_cast<float>(ii);
        float ac = ii==0? 4:1;
        mechanicList_.emplace_back(new MoveEntity(160+i, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                                  Target(TARGET_POS, {500.f + 450.f*std::cos(2.f*i*PI/16.f - PI/2),
                                                                            500.f + 450.f*std::sin(2.f*i*PI/16.f - PI/2)}),500, false));

        mechanicList_.emplace_back(new Spread(160 + i, 200, 1, ac,
                                              Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));



        mechanicList_.emplace_back(new MoveEntity(160+i, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                                  Target(TARGET_POS, {500.f + 450.f*std::cos(2.f*i*PI/16.f + PI/2),
                                                                            500.f + 450.f*std::sin(2.f*i*PI/16.f + PI/2)}),500, false));

        mechanicList_.emplace_back(new Spread(160 + i, 200, 1, ac,
                                              Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    }


    mechanicList_.emplace_back(new Tether(176,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(176,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(180,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(184,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(188,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(180,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(184,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(188,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          800, 4, false, false));



    for(int ii = 0; ii < 13; ii++) {
        auto i = static_cast<float>(ii);
        float ac = ii==0? 4:1;
        mechanicList_.emplace_back(new MoveEntity(192+i, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                                  Target(TARGET_POS, {500.f + 450.f*std::cos(2.f*i*PI/16.f + PI),
                                                                            500.f + 450.f*std::sin(2.f*i*PI/16.f + PI)}),500, false));

        mechanicList_.emplace_back(new Spread(192 + i, 200, 1, ac,
                                              Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));



        mechanicList_.emplace_back(new MoveEntity(192+i, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                                  Target(TARGET_POS, {500.f + 450.f*std::cos(2.f*i*PI/16.f),
                                                                            500.f + 450.f*std::sin(2.f*i*PI/16.f)}),500, false));

        mechanicList_.emplace_back(new Spread(192 + i, 200, 1, ac,
                                              Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    }



    mechanicList_.emplace_back(new Spread(208, 300, 2, 4,
                                          Target(TARGET_POS, {500,500})));


    mechanicList_.emplace_back(new ActivateTotem(212, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    mechanicList_.emplace_back(new ActivateTotem(212, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));


    // COUPLET 1

    mechanicList_.emplace_back(new Spread(216, 200, 2, 8,
                                          Target(TARGET_POS,{500.f,500.f})));

    mechanicList_.emplace_back(new Tether(217.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 4, false, false));

    mechanicList_.emplace_back(new Spread(219, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(219.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(220, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(220.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(221, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(221.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(222, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(223, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanicList_.emplace_back(new Spread(219, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(219.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(220, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(220.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(221, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(221.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(222, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(223, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));




    mechanicList_.emplace_back(new Spread(224, 200, 2, 8,
                                          Target(TARGET_POS,{500.f,500.f})));

    mechanicList_.emplace_back(new Tether(225.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 4, false, false));

    mechanicList_.emplace_back(new Spread(227, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(227.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(228, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(228.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(229.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(230, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(231, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanicList_.emplace_back(new Spread(227, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(227.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(228, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(228.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(229.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(230, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(231, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    mechanicList_.emplace_back(new Spread(232, 200, 2, 8,
                                          Target(TARGET_POS,{500.f,500.f})));

    mechanicList_.emplace_back(new Tether(233.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 4, false, false));

    mechanicList_.emplace_back(new Spread(235, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(235.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(236, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(236.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(237, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(237.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(238, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(239, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanicList_.emplace_back(new Spread(235, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(235.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(236, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(236.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(237, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(237.5, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(238, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(239, 70, 0, 1,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    mechanicList_.emplace_back(new Spread(240, 200, 2, 8,
                                          Target(TARGET_POS,{500.f,500.f})));

    mechanicList_.emplace_back(new Spread(244, 300, 1, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanicList_.emplace_back(new Spread(244, 300, 1, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new Spread(247.5, 300, 2, 3.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(247.5, 300, 2, 3.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    // COUPLET 3

    for(int ii = 0; ii < 3; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(252 + 4*i, 300, 1, 4,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanicList_.emplace_back(new Spread(254 + 4*i, 300, 0, 2,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanicList_.emplace_back(new Spread(252 + 4*i, 300, 1, 4,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanicList_.emplace_back(new Spread(254 + 4*i, 300, 0, 2,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    }

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(264 + 2*i, 100, 1, 2,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanicList_.emplace_back(new Spread(265 + 2*i, 100, 0, 1,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanicList_.emplace_back(new Spread(264 + 2*i, 100, 1, 2,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanicList_.emplace_back(new Spread(265 + 2*i, 100, 0, 1,
                                              Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    }


    mechanicList_.emplace_back(new Spread(278, 300, 2, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));


    mechanicList_.emplace_back(new Spread(280, 200, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 300.f*std::cos(2.f*PI/16.f -PI/4),
                                                  500.f + 300.f*std::sin(2.f*PI/16.f -PI/4)})));
    mechanicList_.emplace_back(new Spread(280, 200, 1, 4,
                                          Target(TARGET_POS,
                                                 {500.f + 300.f*std::cos(PI+2.f*PI/16.f - PI/4),
                                                  500.f + 300.f*std::sin(PI+2.f*PI/16.f - PI/4)})));




    // INTRO

    for(int ii = 0; ii < 26; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(282+i+0.5f, 100, 1, 4,
                                              Target(TARGET_POS,
                                                     {500.f + 350.f*std::cos(2.f*i*PI/16.f -PI/4),
                                                      500.f + 350.f*std::sin(2.f*i*PI/16.f -PI/4)})));
        mechanicList_.emplace_back(new Spread(282+i+0.5f, 100, 1, 4,
                                              Target(TARGET_POS,
                                                     {500.f + 350.f*std::cos(PI+2.f*i*PI/16.f - PI/4),
                                                      500.f + 350.f*std::sin(PI+2.f*i*PI/16.f - PI/4)})));

    }

    // RAMPUP

    mechanicList_.emplace_back(new MoveEntity(308, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
                                              Target(TARGET_POS, {300, 50}),-1, true));
    mechanicList_.emplace_back(new ActivateTotem(308, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));

    mechanicList_.emplace_back(new MoveEntity(308, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
                                              Target(TARGET_POS, {700, 50}),-1, true));
    mechanicList_.emplace_back(new ActivateTotem(308, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));


    mechanicList_.emplace_back(new Tether(342,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
                                          300, 34, true, true));

    mechanicList_.emplace_back(new Tether(342,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
                                          300, 34, true, true));

    mechanicList_.emplace_back(new Spread(312, 150, 2, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new MoveEntity(312, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
                                              Target(TARGET_POS, {300, 500}),200, false));

    mechanicList_.emplace_back(new MoveEntity(312, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
                                              Target(TARGET_POS, {700, 500}),200, false));

    mechanicList_.emplace_back(new Spread(316, 150, 2, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new Spread(318, 150, 1, 2,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new Spread(318.5, 150, 1, 2.5,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));



    mechanicList_.emplace_back(new Spread(320, 150, 2, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new MoveEntity(320, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
                                              Target(TARGET_POS, {300, 950}),200, false));

    mechanicList_.emplace_back(new MoveEntity(320, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
                                              Target(TARGET_POS, {700, 950}),200, false));

    mechanicList_.emplace_back(new Spread(324, 150, 2, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new Spread(326, 150, 1, 2,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanicList_.emplace_back(new Spread(326.5, 150, 1, 2,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));




    mechanicList_.emplace_back(new Spread(328, 150, 2, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new MoveEntity(328, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
                                              Target(TARGET_POS, {50, 500}),300, false));

    mechanicList_.emplace_back(new MoveEntity(328, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
                                              Target(TARGET_POS, {450, 500}),300, false));

    mechanicList_.emplace_back(new Spread(332, 150, 2, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new MoveEntity(332, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
                                              Target(TARGET_POS, {300, 50}),300, false));

    mechanicList_.emplace_back(new MoveEntity(332, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
                                              Target(TARGET_POS, {700, 50}),300, false));

    mechanicList_.emplace_back(new Spread(336, 150, 2, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new MoveEntity(336, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
                                              Target(TARGET_POS, {550, 500}),300, false));

    mechanicList_.emplace_back(new MoveEntity(336, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
                                              Target(TARGET_POS, {950, 500}),300, false));


    mechanicList_.emplace_back(new Spread(340, 150, 2, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new Spread(342, 150, 1, 2,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanicList_.emplace_back(new Spread(342.5, 150, 1, 2,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));


    mechanicList_.emplace_back(new ActivateTotem(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false));
    mechanicList_.emplace_back(new ActivateTotem(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), false));


    // REFRAIN 1

    mechanicList_.emplace_back(new MoveEntity(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                              Target(TARGET_POS, {500, 50}),-1, true));
    mechanicList_.emplace_back(new ActivateTotem(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));

    mechanicList_.emplace_back(new MoveEntity(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                              Target(TARGET_POS, {500, 950}),-1, true));
    mechanicList_.emplace_back(new ActivateTotem(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));

    mechanicList_.emplace_back(new Tether(348,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(348,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          300, 4, true, false));


    mechanicList_.emplace_back(new Tether(352,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(356,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(360,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(352,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(356,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(360,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          800, 4, false, false));

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(348, 250, 0, 4,
                                              Target(TARGET_POS, {750,i*250})));
    }

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(352, 250, 0, 4,
                                              Target(TARGET_POS, {250,i*250})));
    }

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(356, 250, 0, 4,
                                              Target(TARGET_POS, {750,i*250})));
    }

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(360, 250, 0, 4,
                                              Target(TARGET_POS, {250,i*250})));
    }





    for(int ii = 0; ii < 13; ii++) {
        auto i = static_cast<float>(ii);
        float ac = ii==0? 4:1;
        mechanicList_.emplace_back(new MoveEntity(364+i, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                                  Target(TARGET_POS, {500.f + 450.f*std::cos(2.f*i*PI/16.f - PI/2),
                                                                      500.f + 450.f*std::sin(2.f*i*PI/16.f - PI/2)}),500, false));

        mechanicList_.emplace_back(new Spread(364 + i, 200, 1, ac,
                                              Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));



        mechanicList_.emplace_back(new MoveEntity(364+i, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                                  Target(TARGET_POS, {500.f + 450.f*std::cos(2.f*i*PI/16.f + PI/2),
                                                                      500.f + 450.f*std::sin(2.f*i*PI/16.f + PI/2)}),500, false));

        mechanicList_.emplace_back(new Spread(364 + i, 200, 1, ac,
                                              Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    }



    mechanicList_.emplace_back(new Tether(380,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(384,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(388,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(392,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(380,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(384,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          800, 4, false, false));

    mechanicList_.emplace_back(new Tether(388,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          300, 4, true, false));

    mechanicList_.emplace_back(new Tether(392,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                          800, 4, false, false));

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(380, 250, 0, 4,
                                              Target(TARGET_POS, {i*250, 250+500.f*(ii<3)})));
    }

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(384, 250, 0, 4,
                                              Target(TARGET_POS, {i*250, 250+500.f*(ii>=3)})));
    }


    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(388, 250, 0, 4,
                                              Target(TARGET_POS, {i*250, 250})));
    }

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(392, 250, 0, 4,
                                              Target(TARGET_POS, {i*250, 750})));
    }



    for(int ii = 0; ii < 13; ii++) {
        auto i = static_cast<float>(ii);
        float ac = ii==0? 4:1;
        mechanicList_.emplace_back(new MoveEntity(396+i, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                                  Target(TARGET_POS, {500.f + 450.f*std::cos(2.f*i*PI/16.f + PI),
                                                                      500.f + 450.f*std::sin(2.f*i*PI/16.f + PI)}),500, false));

        mechanicList_.emplace_back(new Spread(396 + i, 200, 1, ac,
                                              Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));



        mechanicList_.emplace_back(new MoveEntity(396+i, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                                  Target(TARGET_POS, {500.f + 450.f*std::cos(2.f*i*PI/16.f),
                                                                      500.f + 450.f*std::sin(2.f*i*PI/16.f)}),500, false));

        mechanicList_.emplace_back(new Spread(396 + i, 200, 1, ac,
                                              Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    }

    mechanicList_.emplace_back(new ActivateTotem(408, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    mechanicList_.emplace_back(new ActivateTotem(408, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));



    // OUTRO

    for(int i = 0; i < 6; i++) {
            mechanicList_.emplace_back(new Spread(412, 200, 0, 4,
                                                  Target(TARGET_POS, {i*200.f, 400.f})));

        mechanicList_.emplace_back(new Spread(412, 200, 0, 4,
                                              Target(TARGET_POS, {400.f, i*200.f})));
    }

    mechanicList_.emplace_back(new Spread(416, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(416, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for(int i = 0; i < 6; i++) {
        mechanicList_.emplace_back(new Spread(416, 200, 0, 4,
                                              Target(TARGET_POS, {i*200.f, 600.f})));

        mechanicList_.emplace_back(new Spread(416, 200, 0, 4,
                                              Target(TARGET_POS, {600.f, i*200.f})));
    }

    mechanicList_.emplace_back(new Spread(420, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(420, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for(int i = 0; i < 6; i++) {
        mechanicList_.emplace_back(new Spread(420, 200, 0, 4,
                                              Target(TARGET_POS, {i*200.f, 600.f})));

        mechanicList_.emplace_back(new Spread(420, 200, 0, 4,
                                              Target(TARGET_POS, {400.f, i*200.f})));
    }

    mechanicList_.emplace_back(new Spread(424, 224, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(424, 224, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for(int i = 0; i < 6; i++) {
        mechanicList_.emplace_back(new Spread(424, 200, 0, 4,
                                              Target(TARGET_POS, {i*200.f, 400.f})));

        mechanicList_.emplace_back(new Spread(424, 200, 0, 4,
                                              Target(TARGET_POS, {600.f, i*200.f})));
    }

    mechanicList_.emplace_back(new Spread(428, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(428, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for(int i = 0; i < 6; i++) {
        mechanicList_.emplace_back(new Spread(428, 200, 0, 4,
                                              Target(TARGET_POS, {i*200.f, i*200.f})));

        mechanicList_.emplace_back(new Spread(428, 200, 0, 4,
                                              Target(TARGET_POS, {(5.f-i)*200.f, i*200.f})));
    }

    mechanicList_.emplace_back(new Spread(432, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(432, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for(int i = 0; i < 6; i++) {
        mechanicList_.emplace_back(new Spread(432, 200, 0, 4,
                                              Target(TARGET_POS, {i*200.f, 500})));

        mechanicList_.emplace_back(new Spread(432, 200, 0, 4,
                                              Target(TARGET_POS, {500, i*200.f})));
    }

    mechanicList_.emplace_back(new Spread(436, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(436, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for(int i = 0; i < 6; i++) {
        mechanicList_.emplace_back(new Spread(436, 200, 0, 4,
                                              Target(TARGET_POS, {i*200.f, i*200.f})));

        mechanicList_.emplace_back(new Spread(436, 200, 0, 4,
                                              Target(TARGET_POS, {(5.f-i)*200.f, i*200.f})));
    }

    mechanicList_.emplace_back(new Spread(440, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanicList_.emplace_back(new Spread(440, 200, 0, 4,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for(int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(440, 200, 0, 4,
                                              Target(TARGET_POS, {i*200.f, 500})));

        mechanicList_.emplace_back(new Spread(440, 200, 0, 4,
                                              Target(TARGET_POS, {500, i*200.f})));
    }

    mechanicList_.emplace_back(new ApplyDebuff(440, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT), DEBUFF_ROOT, 4));

    for(int ii = 0; ii < 16; ii++) {
        auto i = static_cast<float>(ii);

        if(ii != 15)
            mechanicList_.emplace_back(new ApplyDebuff(444+2*i, Target(TARGET_ENTITY, TARGET_PLAYERS, ii%2, TARGET_ONINIT), DEBUFF_ROOT, 2));

        mechanicList_.emplace_back(new Spread(444+2*i, 200, 1, 4,
                                              Target(TARGET_POS, {500.f + 250.f*std::cos(2.f*i*PI/4.f),
                                                                  500.f + 250.f*std::sin(2.f*i*PI/4.f)})));


    }

    mechanicList_.emplace_back(new Spread(476, 200, 2, 4,
                                          Target(TARGET_POS, {500.f, 500.f})));




    std::cout << "Mechanics number : " << mechanicList_.size() << std::endl;

    song_.setTime(sf::seconds(173));

    std::sort(mechanicList_.begin(), mechanicList_.end(),
              [] (Mechanic* m1, Mechanic* m2) {return *m1 < *m2;});
}


/*

void Game::load() {

    song_.load("Beatmaps/1772712 DECO 27 - Ai Kotoba IV feat. Hatsune Miku/DECO27 - Ai Kotoba IV feat. Hatsune Miku ([Hatsune Miku]) [Daisuki].osu", mechanicList_);
    for(int i = 0; i < mechanicList_.size(); i++) {
        delete mechanicList_[i];
    }
    mechanicList_.clear();

    mechanicList_.emplace_back(new Spread(32.75, 70, 1, 8, Target(TARGET_POS, {60, 160})));
    mechanicList_.emplace_back(new Spread(33, 70, 1, 4, Target(TARGET_POS, {100, 200})));
    mechanicList_.emplace_back(new Spread(35, 70, 1, 4, Target(TARGET_POS, {300, 200})));
    mechanicList_.emplace_back(new Spread(37, 70, 1, 4, Target(TARGET_POS, {500, 200})));

    mechanicList_.emplace_back(new Spread(39, 70, 2, 4, Target(TARGET_POS, {700, 300})));

    mechanicList_.emplace_back(new Spread(32.75, 70, 1, 8, Target(TARGET_POS, {60, 360})));
    mechanicList_.emplace_back(new Spread(33, 70, 1, 4, Target(TARGET_POS, {100, 400})));
    mechanicList_.emplace_back(new Spread(35, 70, 1, 4, Target(TARGET_POS, {300, 400})));
    mechanicList_.emplace_back(new Spread(37, 70, 1, 4, Target(TARGET_POS, {500, 400})));

    mechanicList_.emplace_back(new Spread(39, 70, 1, 0, Target(TARGET_POS, {400, 300})));

    for(int ii = 0; ii < 12; ii++) {
        auto i = static_cast<float>(ii);
        mechanicList_.emplace_back(new Spread(41 + 2*i, 130, 0, 4,
                                              Target(TARGET_POS,
                                                     {400.f + 250.f*std::cos(2.f*i*PI/8.f),
                                                      300.f + 250.f*std::sin(2.f*i*PI/8.f)})));
        mechanicList_.emplace_back(new Spread(41.f + 2.f*i,130, 0, 4,
                                              Target(TARGET_POS,
                                                     {400.f + 250.f*std::cos(PI+2.f*i*PI/8.f),
                                                      300.f + 250.f*std::sin(PI+2.f*i*PI/8.f)})));

        mechanicList_.emplace_back(new Spread(41 + 2.f*i, 130, 0, 4,
                                              Target(TARGET_POS, {400, 300})));
    }

    mechanicList_.emplace_back(new Spread(5, 100, 1, 4, Target(TARGET_RANDOM, TARGET_PLAYERS, TARGET_FOLLOW)));

     mechanicList_.emplace_back(new Tether(70,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 70, true, true));

    mechanicList_.emplace_back(new Tether(21,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
                                          300, 4, false, false));

    mechanicList_.emplace_back(new ActivateTotem(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanicList_.emplace_back(new MoveEntity(2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
                                              Target(TARGET_POS, {100, 100}),-1, true));

    mechanicList_.emplace_back(new ActivateTotem(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanicList_.emplace_back(new MoveEntity(2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
                                              Target(TARGET_POS, {300, 100}),-1, true));

    mechanicList_.emplace_back(new ActivateTotem(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanicList_.emplace_back(new MoveEntity(2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
                                              Target(TARGET_POS, {500, 100}),-1, true));

    mechanicList_.emplace_back(new ActivateTotem(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanicList_.emplace_back(new MoveEntity(2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
                                              Target(TARGET_POS, {700, 100}),-1, true));


    mechanicList_.emplace_back(new Spread(5, 100, 0, 4, Target(TARGET_RANDOM4, TARGET_TOTEMS, TARGET_FOLLOW)));
    mechanicList_.emplace_back(new Spread(5, 100, 0, 4, Target(TARGET_RANDOM_END, TARGET_TOTEMS, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new Spread(9, 100, 0, 4, Target(TARGET_RANDOM4, TARGET_TOTEMS, TARGET_FOLLOW)));
    mechanicList_.emplace_back(new Spread(9, 100, 0, 4, Target(TARGET_RANDOM4, TARGET_TOTEMS, TARGET_FOLLOW)));
    mechanicList_.emplace_back(new Spread(9, 100, 0, 4, Target(TARGET_RANDOM_END, TARGET_TOTEMS, TARGET_FOLLOW)));

    mechanicList_.emplace_back(new ApplyDebuff(5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_ROOT, 2));

    mechanicList_.emplace_back(new Tether(13,
                                          Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
                                          Target(TARGET_FURTHEST, TARGET_TOTEMS, 0, new Target(TARGET_ENTITY, TARGET_PLAYERS, 0), TARGET_ONINIT),
                                          100, 4, true, false));



    std::sort(mechanicList_.begin(), mechanicList_.end(),
              [] (Mechanic* m1, Mechanic* m2) {return *m1 < *m2;});
}
     */

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




