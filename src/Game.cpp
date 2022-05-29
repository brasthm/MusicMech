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

    std::vector<Mechanic*> mechanicList;
    Song s("Beatmaps/546820 YUC'e - Future Candy/YUC'e - Future Candy (Nathan) [Normal].osu", mechanicList);

    s.play();

    for(int i = 0; i < mechanicList.size(); i++) {
        delete mechanicList[i];
    }
    mechanicList.clear();

    mechanicList.emplace_back(new Tower(32.75, {60, 160}, 70, 1, 8));
    mechanicList.emplace_back(new Tower(33, {100, 200}, 70, 1, 4));
    mechanicList.emplace_back(new Tower(35, {300, 200}, 70, 1, 4));
    mechanicList.emplace_back(new Tower(37, {500, 200}, 70, 1, 4));

    mechanicList.emplace_back(new Tower(39, {700, 300}, 70, 2, 4));

    mechanicList.emplace_back(new Tower(32.75, {60, 360}, 70, 1, 8));
    mechanicList.emplace_back(new Tower(33, {100, 400}, 70, 1, 4));
    mechanicList.emplace_back(new Tower(35, {300, 400}, 70, 1, 4));
    mechanicList.emplace_back(new Tower(37, {500, 400}, 70, 1, 4));

    mechanicList.emplace_back(new Tower(39, {400, 300}, 70, 1, 0));

    while (window_.isOpen())
    {
        sf::Event event;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        sf::Time currentPos = s.getCurrentTime();
        float currentBeat_float = s.getCumulativeNBeats(currentPos.asMilliseconds());
        currentBeat = (int) currentBeat_float;

        fps_text.setString(std::to_string(currentBeat_float));


        sf::Time elapsedTime = fps.getElapsedTime();
        fps.restart();
        for(int i = 0; i < joueurs_.size(); i++) {
            joueurs_[i].update(elapsedTime, window_.hasFocus());
        }

        for(int i = 0; i < mechanicList.size(); i++) {
            mechanicList[i]->update(elapsedTime, currentBeat_float, joueurs_);
        }




        if(send.getElapsedTime().asMilliseconds() > CLIENT_TICK_MS) {
            client_->sendPlayerData((int)joueurs_[current].getPosX(), (int)joueurs_[current].getPosY());
            send.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            displayTest.restart();
            currentBeat = 0;
        }



        client_->updateFromServerPlayerPosition(joueurs_);
        window_.clear(sf::Color(0x2A2431FF));


        for(int i = 0; i < mechanicList.size(); i++) {
            mechanicList[mechanicList.size() - i - 1]->draw(window_);
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



