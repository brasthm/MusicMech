//
// Created by cyril on 16/05/2022.
//

#include <iostream>

#include "Game.h"
#include "main.h"
#include "RingShape.h"
#include "RessourceLoader.h"
#include "Mechanic.h"
#include "Tower.h"
#include "Song.h"

Game::Game(sf::RenderWindow &window) : window_(window), client_(nullptr){
    online_ = false;
}

Game::Game(sf::RenderWindow &window, Client *client) : window_(window), client_(client) {
    online_ = true;
}


void Game::run() {

    for(int i = 0; i < NB_MAX_JOUEURS; i++) {
        joueurs_.emplace_back();
    }

    if(online_) {
        int n = 0;
        bool conn = false;
        while(n < 5 && !conn) {
            conn = client_->connectToServer();
            n++;
        }
        if(conn) {
            std::cout << "Connected to server" << std::endl;
        }
        else {
            std::cout << "Failed to connect to server" << std::endl;
            return;
        }
    }


    sf::Clock fps, send;

    int current = client_->getIndex();

    sf::Text fps_text;

    fps_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    fps_text.setCharacterSize(30);

    joueurs_[current].setConnected(true);
    joueurs_[current].setControlledByPlayer(true);

    sf::Clock displayTest;

    int currentBeat = 0;
    float BPM = 142;
    int offset = 70;

    std::vector<Mechanic*> mechanicList;

    Song s = Song("Beatmaps/461509 Marshmello - Alone/Marshmello - Alone (Zer0-) [Lonely].osu", mechanicList);

    s.play();


    while (window_.isOpen())
    {
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        for(int i = 0; i < 1; i++) {
            joueurs_[i].update(fps.getElapsedTime(), window_.hasFocus());
        }

        fps.restart();

        if(send.getElapsedTime().asMilliseconds() > CLIENT_TICK_MS) {
            client_->sendPlayerData((int)joueurs_[current].getPosX(), (int)joueurs_[current].getPosY());
            send.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            displayTest.restart();
            currentBeat = 0;
        }

        
        sf::Time currentPos = s.getCurrentTime();
        float propTime = currentPos.asMilliseconds() - 0.6 * (currentPos.asMilliseconds() - offset) / BPM;

        currentBeat = 0.6 * (currentPos.asMilliseconds() - offset) / BPM;

        for(int i = 0; i < mechanicList.size(); i++) {
            mechanicList[i]->update(currentBeat, propTime);
        }


        if(propTime > 1) {
            displayTest.restart();
            currentBeat++;
        }


        fps_text.setString(std::to_string(currentBeat));

        client_->updateFromServerPlayerPosition(joueurs_);

        window_.clear();


        for(int i = 0; i < mechanicList.size(); i++) {
            mechanicList[i]->draw(window_);
        }

        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
            joueurs_[i].draw(window_);
        }

        window_.draw(fps_text);

        window_.display();
    }

    if(online_) {
        int n = 0;
        bool dced = false;

        while(n < 5 && !dced) {
            dced = client_->disconectToServer();
            n++;
        }
        if(dced) {
            std::cout << "Disconnected to server" << std::endl;
        }
        else {
            std::cout << "Failed to disconnect to server" << std::endl;
        }
    }

    for(int i = 0; i < mechanicList.size(); i++) {
        delete mechanicList[i];
    }


}



