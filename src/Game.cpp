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


    sf::Clock fps, send;

    int current = client_->getIndex();

    sf::Text fps_text;

    fps_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    fps_text.setCharacterSize(30);

    joueurs_[current].setActive(true);
    joueurs_[current].setControlledByPlayer(true);

    std::cout << "Current : " << current << std::endl;


    sf::Clock displayTest;

    song_.play();

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
            joueurs_[i].update(elapsedTime, currentBeat_float, window.hasFocus());
        }

        for(int  i = 0; i < NB_MAX_TOTEM; i++) {
            totems_[i].update(elapsedTime, currentBeat_float, window.hasFocus());
        }

        for(int i = 0; i < mechanicList_.size(); i++) {
            mechanicList_[i]->update(elapsedTime, currentBeat_float, em_);
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
                                          300, 40, true, true));

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

    std::sort(mechanicList_.begin(), mechanicList_.end(), compareMech);
}

Game::~Game() {
    for(int i = 0; i < mechanicList_.size(); i++) {
        delete mechanicList_[i];
    }
}

bool Game::compareMech(Mechanic *m1, Mechanic *m2) {
    return *m1 < *m2;
}



