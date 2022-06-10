//
// Created by cyril on 16/05/2022.
//

#include <iostream>
#include <cmath>

#include "Game.h"
#include "main.h"
#include "RingShape.h"
#include "RessourceLoader.h"
#include "Mechanic.h"
#include "Tower.h"
#include "Song.h"
#include "Spread.h"

Game::Game() : client_(nullptr){
    online_ = false;
}

Game::Game(Client *client) :client_(client) {
    online_ = true;
}


void Game::run(sf::RenderWindow &window) {

    for(int i = 0; i < NB_MAX_JOUEURS; i++) {
        joueurs_.emplace_back();
    }


    sf::Clock fps, send;

    int current = client_->getIndex();

    sf::Text fps_text;

    fps_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    fps_text.setCharacterSize(30);

    joueurs_[current].setConnected(true);
    joueurs_[current].setControlledByPlayer(true);

    std::cout << "Current : " << current << std::endl;

    sf::Clock displayTest;

    int currentBeat = 0;

    std::vector<Mechanic*> mechanicList;
    Song s("Beatmaps/546820 YUC'e - Future Candy/YUC'e - Future Candy (Nathan) [Normal].osu", mechanicList);

    s.play();

    for(int i = 0; i < mechanicList.size(); i++) {
        delete mechanicList[i];
    }
    mechanicList.clear();

    mechanicList.emplace_back(new Tower(32.75, {60, 160}, 70, 0, 8));
    mechanicList.emplace_back(new Tower(33, {100, 200}, 70, 1, 4));
    mechanicList.emplace_back(new Tower(35, {300, 200}, 70, 1, 4));
    mechanicList.emplace_back(new Tower(37, {500, 200}, 70, 1, 4));

    mechanicList.emplace_back(new Tower(39, {700, 300}, 70, 2, 4));

    mechanicList.emplace_back(new Tower(32.75, {60, 360}, 70, 1, 8));
    mechanicList.emplace_back(new Tower(33, {100, 400}, 70, 1, 4));
    mechanicList.emplace_back(new Tower(35, {300, 400}, 70, 1, 4));
    mechanicList.emplace_back(new Tower(37, {500, 400}, 70, 1, 4));

    mechanicList.emplace_back(new Tower(39, {400, 300}, 70, 1, 0));

    mechanicList.emplace_back(new Spread(25, {100, 200}, 100, 1, 4, &joueurs_[0]));

    for(int  i = 0; i < 12; i++) {
        mechanicList.emplace_back(new Spread(41 + 2*i,
                                             {static_cast<float>(400 + 250*cos(2*i*PI/8)),
                                                        static_cast<float>(300 + 250*sin(2*i*PI/8))},
                                             130, 0, 4, nullptr));
        mechanicList.emplace_back(new Spread(41 + 2*i,
                                             {static_cast<float>(400 + 250*cos(PI+2*i*PI/8)),
                                              static_cast<float>(300 + 250*sin(PI+2*i*PI/8))},
                                             130, 0, 4, nullptr));

        mechanicList.emplace_back(new Spread(41 + 2*i,
                                             {400, 300},
                                             130, 0, 4, nullptr));
    }
    bool exit=false;
    while (!exit)
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit=true;
        }

        sf::Time currentPos = s.getCurrentTime();
        float currentBeat_float = s.getCumulativeNBeats(currentPos.asMilliseconds());
        currentBeat = (int) currentBeat_float;

        fps_text.setString(std::to_string(currentBeat_float));


        sf::Time elapsedTime = fps.getElapsedTime();
        fps.restart();
        for(int i = 0; i < joueurs_.size(); i++) {
            joueurs_[i].update(elapsedTime, window.hasFocus());
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
        window.clear(sf::Color(0x2A2431FF));


        for(int i = 0; i < mechanicList.size(); i++) {
            mechanicList[mechanicList.size() - i - 1]->draw(window);
        }

        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
            joueurs_[i].draw(window);
        }

        window.draw(fps_text);

        window.display();
    }

    for(int i = 0; i < mechanicList.size(); i++) {
        delete mechanicList[i];
    }


}



