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
#include "Mechanics/Tower.h"
#include "Mechanics/Spread.h"
#include "Mechanics/Tether.h"
#include "Mechanics/ActivateTotem.h"
#include "Mechanics/MoveEntity.h"

#include "System/Song.h"

Game::Game() : client_(nullptr){
    online_ = false;
}

Game::Game(Client *client) :client_(client) {
    online_ = true;
    for(int i = 0; i < NB_MAX_TOTEM; i++)
        totems_.emplace_back();
}


void Game::run(sf::RenderWindow &window, const std::string& roomID) {

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


    mechanicList_.emplace_back(new Spread(25, {100, 200}, 100, 1, 4, &joueurs_[0]));
    mechanicList_.emplace_back(new Tether(50, &joueurs_[0], &joueurs_[1], 300, 40, true, true));

    mechanicList_.emplace_back(new Tether(7, &joueurs_[0], &joueurs_[1], 300, 4, false, false));

    mechanicList_.emplace_back(new ActivateTotem(0, &totems_[0], true));

    mechanicList_.emplace_back(new MoveEntity(2, &totems_[0], {100, 100}, -1, true));
    mechanicList_.emplace_back(new MoveEntity(3, &totems_[0], {200, 100}, -1, true));
    mechanicList_.emplace_back(new MoveEntity(4, &totems_[0], {500, 500}, 200, false));

    song_.play();

    std::sort(mechanicList_.begin(), mechanicList_.end(), compareMech);

    for(int i = 0; i < mechanicList_.size(); i++)
        std::cout << mechanicList_[i]->getDrawPriority() << " " << mechanicList_[i]->getBeat() << std::endl;


    bool exit=false, interupted=false;
    while (!exit)
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                exit=true;
        }

        sf::Time currentPos = song_.getCurrentTime();
        float currentBeat_float = song_.getCumulativeNBeats(currentPos.asMilliseconds());

        fps_text.setString(std::to_string(currentBeat_float));


        sf::Time elapsedTime = fps.getElapsedTime();
        fps.restart();
        for(int i = 0; i < joueurs_.size(); i++) {
            joueurs_[i].update(elapsedTime, window.hasFocus());
        }

        for(int  i = 0; i < NB_MAX_TOTEM; i++) {
            totems_[i].update(elapsedTime, window.hasFocus());
        }

        for(int i = 0; i < mechanicList_.size(); i++) {
            mechanicList_[i]->update(elapsedTime, currentBeat_float, joueurs_);
        }

        if(send.getElapsedTime().asMilliseconds() > CLIENT_TICK_MS) {
            client_->sendPlayerData((int)joueurs_[current].getPosX(), (int)joueurs_[current].getPosY());
            send.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            displayTest.restart();
            load();
        }

        if(!exit) {
            interupted = !client_->updateFromServerPlayerPosition(joueurs_);
            exit = interupted;
        }

        window.clear(sf::Color(0x2A2431FF));

        for(int i = 0; i < mechanicList_.size(); i++) {
            mechanicList_[i]->draw(elapsedTime, window);
        }

        for(int  i = 0; i < NB_MAX_TOTEM; i++) {
            totems_[i].draw(window);
        }

        for(int i = 0; i < NB_MAX_JOUEURS; i++) {
            joueurs_[i].draw(window);
        }




        window.draw(fps_text);

        window.display();
    }

    if(!interupted)
        client_->sendEndGame(roomID);

    load();

}

void Game::load() {

    song_.load("Beatmaps/546820 YUC'e - Future Candy/YUC'e - Future Candy (Nathan) [Normal].osu", mechanicList_);
    for(int i = 0; i < mechanicList_.size(); i++) {
        delete mechanicList_[i];
    }
    mechanicList_.clear();

    mechanicList_.emplace_back(new Spread(32.75, {60, 160}, 70, 0, 8, nullptr));
    mechanicList_.emplace_back(new Spread(33, {100, 200}, 70, 1, 4, nullptr));
    mechanicList_.emplace_back(new Spread(35, {300, 200}, 70, 1, 4, nullptr));
    mechanicList_.emplace_back(new Spread(37, {500, 200}, 70, 1, 4, nullptr));

    mechanicList_.emplace_back(new Spread(39, {700, 300}, 70, 2, 4, nullptr));

    mechanicList_.emplace_back(new Spread(32.75, {60, 360}, 70, 1, 8, nullptr));
    mechanicList_.emplace_back(new Spread(33, {100, 400}, 70, 1, 4, nullptr));
    mechanicList_.emplace_back(new Spread(35, {300, 400}, 70, 1, 4, nullptr));
    mechanicList_.emplace_back(new Spread(37, {500, 400}, 70, 1, 4, nullptr));

    mechanicList_.emplace_back(new Spread(39, {400, 300}, 70, 1, 0, nullptr));

    for(int  i = 0; i < 12; i++) {
        mechanicList_.emplace_back(new Spread(41 + 2*i,
                                              {static_cast<float>(400 + 250*cos(2*i*PI/8)),
                                               static_cast<float>(300 + 250*sin(2*i*PI/8))},
                                              130, 0, 4, nullptr));
        mechanicList_.emplace_back(new Spread(41 + 2*i,
                                              {static_cast<float>(400 + 250*cos(PI+2*i*PI/8)),
                                               static_cast<float>(300 + 250*sin(PI+2*i*PI/8))},
                                              130, 0, 4, nullptr));

        mechanicList_.emplace_back(new Spread(41 + 2*i,
                                              {400, 300},
                                              130, 0, 4, nullptr));
    }

}

Game::~Game() {
    for(int i = 0; i < mechanicList_.size(); i++) {
        delete mechanicList_[i];
    }
}

bool Game::compareMech(Mechanic *m1, Mechanic *m2) {
    return *m1 < *m2;
}



