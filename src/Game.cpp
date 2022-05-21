//
// Created by cyril on 16/05/2022.
//

#include <iostream>

#include "Game.h"
#include "main.h"
#include "RingShape.h"
#include "RessourceLoader.h"

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

    std::cout << current << std::endl;

    RingShape test_shape(sf::Vector2f(400,300), 20, 10, 0);

    sf::Text fps_text;

    fps_text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    fps_text.setCharacterSize(30);

    joueurs_[current].setConnected(true);
    joueurs_[current].setControlledByPlayer(true);

    sf::Clock displayTest;

    float BPM = 119.92;
    int count = 0;


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
            count = 0;
        }

        float propTime = displayTest.getElapsedTime().asSeconds()*BPM/60;
        if(propTime < 0.25) {
            test_shape.setProportion(0.25 * count + 0.25*(propTime)/0.25);
        }
        if(propTime > 1) {
            displayTest.restart();
            count++;
            if(count == 4) {
                count = 0;
            }
        }




        fps_text.setString(std::to_string(0.25 * count + (propTime-0.75)));

        client_->updateFromServerPlayerPosition(joueurs_);

        window_.clear();


        test_shape.draw(window_);

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
}



