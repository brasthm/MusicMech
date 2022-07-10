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

    music_.play();

    bool exit=false, interupted=false, sent=false, failed = false, resume=false;

    std::pair<float, float> checkpoint;

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
            if (event.type == sf::Event::Closed)
                exit=true;
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::G) {
                    godmode = true;
                }
                if(event.key.code == sf::Keyboard::H) {
                    godmode = false;
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
                //newfailed = newfailed || mech->isFailed();
            }

            if(send.getElapsedTime().asMilliseconds() > CLIENT_TICK_MS) {
                client_->sendPlayerData((int)joueurs_[current].getPosX(), (int)joueurs_[current].getPosY());
                send.restart();
            }
        }

        if(!exit) {
            int res = client_->updateFromServerPlayerPosition(joueurs_, checkpoint);
            interupted = res == 1;
            newfailed = res == 2;
            if(failed) resume = res == 3;
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
                client_->sendResumeGame(roomID);
                resume = true;
            }
        }

        if(resume) {
            sent = false;
            failed = false;
            music_.play();
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
            "Beatmaps/1772712 DECO 27 - Ai Kotoba IV feat. Hatsune Miku/[2P] DECO27 - Ai Kotoba IV feat. Hatsune Miku.mm",
            //"Beatmaps/1772712 DECO 27 - Ai Kotoba IV feat. Hatsune Miku/[TEST] DECO27 - Ai Kotoba IV feat. Hatsune Miku.mm",
            &music_,
            mechanicList_);



    std::sort(mechanicList_.begin(), mechanicList_.end(),
              [] (Mechanic* m1, Mechanic* m2) {return *m1 < *m2;});
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

void Game::save(const std::string &filename) {
    song_.save(filename, mechanicList_);
}




