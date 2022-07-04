//
// Created by cyril on 01/06/2022.
//

#include "LobbyMenu.h"
#include "System/RessourceLoader.h"
#include "System/Random.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <random>

int LobbyMenu::run(sf::RenderWindow &window, Game &game, Client &client) {
    bool quit = false;
    int state = 0;

    std::cout << "Connecting to server..." << std::endl;

    bool ok = false;
    for(int i = 0; i < 5; i++) {
        if(client.connectToServer()) {
            ok = true;
            break;
        }
    }

    if(!ok) {
        std::cout << "Unable to connect to server" << std::endl;
        return -1;
    }

    std::cout << "Connected to server" << std::endl;

    ok = false;

    for(int i = 0; i < 10; i++) {
        if(client.requestLobbyList(lobbyList_)) {
            ok = true;
            break;
        }
    }

    if(!ok) {
        std::cout << "Unable to fectch data" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(RessourceLoader::getFont("font/Roboto-Regular.ttf"));
    text.setCharacterSize(30);

    std::cout << "   1. Create new room" << std::endl;
    std::cout << "   2. Join room" << std::endl;
    std::cout << "   3. Refresh" << std::endl;
    std::cout << "   4. Quit" << std::endl;

    retries_ = 0;

    while (!quit) {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                quit=true;
        }

        if(window.hasFocus()) {
            if(state == 0) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                    std::cout << "Name of the room : ";
                    std::string inp;
                    std::getline(std::cin, inp);
                    std::getline(std::cin, inp);
                    ok = client.requestLobbyCreation(index_, inp);
                    ind_ = findFirstAvailableLobby(lobbyList_);
                    lobbyList_[ind_].id = index_;
                    ok = ok && client.requestLobbyInfo(lobbyList_[ind_], index_);
                    if(ok) state = 1;
                    else std::cout << "Error on lobby room creation" << std::endl;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                    std::cout << "Room index : ";
                    int i;
                    std::cin >> i;
                    ok = client.requestLobbyJoin(lobbyList_, lobbyList_[i].id);
                    if(ok) {
                        index_ = lobbyList_[i].id;
                        ind_ = findLobbyById(lobbyList_, index_);
                        state = 1;
                    }
                    else std::cout << "Error on lobby room conncection" << std::endl;

                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                    client.requestLobbyList(lobbyList_);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
                    quit = true;
            }
            else if(state == 1) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    ok = client.requestLobbyDisconnect(lobbyList_, index_);
                    ok = ok && client.requestLobbyList(lobbyList_);
                    if(ok) state = 0;
                    else std::cout << "Error on deconnection" << std::endl;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    ok = client.requestLaunchGame(index_);
                    if(ok) state = 3;
                    else std::cout << "Error on deconnection" << std::endl;
                }
            }
        }


        if(!client.monitorLobby(lobbyList_, index_, state))
            std::cout << "MONITOR ERROR" << std::endl;
        if(state == 3) { // Launch game
            std::string seedString = index_ + std::to_string(retries_);
            for(int i = 0; i < lobbyList_[ind_].players.size(); i++) {
                seedString+=lobbyList_[ind_].players[i]->name;
            }
            std::cout << seedString << std::endl;
            auto *seed = new std::seed_seq(seedString.begin(), seedString.end());
            Random::setSeed(seed);
            delete seed;
            game.run(window, index_);
            state = 1;
            retries_++;

        }


        window.clear();

        if(state == 0) { // List
            text.setString("ID");
            text.setPosition(90 - text.getGlobalBounds().width, 30);
            window.draw(text);

            text.setString("Player");
            text.setPosition(290 - text.getGlobalBounds().width, 30);
            window.draw(text);

            text.setString("Room");
            text.setPosition(590 - text.getGlobalBounds().width, 30);
            window.draw(text);

            float nb=1;
            for (int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
                if (lobbyList_[i].status != LobbyStatus::LOBBY_AVAILABLE) {

                    text.setString(std::to_string(i));
                    text.setPosition(90 - text.getGlobalBounds().width, 30 + 50*nb);
                    window.draw(text);

                    text.setString(lobbyList_[i].players[0]->name);
                    text.setPosition(290 - text.getGlobalBounds().width, 30 + 50*nb);
                    window.draw(text);

                    text.setString(lobbyList_[i].name);
                    text.setPosition(590 - text.getGlobalBounds().width, 30 +50*nb);
                    window.draw(text);

                    text.setString(lobbyList_[i].name);
                    text.setPosition(590 - text.getGlobalBounds().width, 30 + 50*nb);
                    window.draw(text);

                    std::string sortie = std::to_string(lobbyList_[i].nbIn) + "/" + std::to_string(lobbyList_[i].limit);

                    text.setString(sortie);
                    text.setPosition(690 - text.getGlobalBounds().width, 30 + 50*nb);
                    window.draw(text);
                    nb++;
                }
            }
        }
        else if(state == 1) { // Room
            std::string s =  lobbyList_[ind_].name + " " + std::to_string(lobbyList_[ind_].nbIn)
                    + "/" + std::to_string(lobbyList_[ind_].limit);

            text.setString(s);
            text.setPosition(300, 30);
            window.draw(text);

            text.setString("Player");
            text.setPosition(30, 80);
            window.draw(text);

            float nb=2;
            for(int i = 0; i < NB_MAX_JOUEURS; i++) {
                text.setString(lobbyList_[ind_].players[i]->name);
                text.setPosition(30, 30 + nb*50);
                window.draw(text);
                nb++;
            }
        }

        window.display();
    }

    if(state == 1) {
        client.requestLobbyDisconnect(lobbyList_, index_);
    }

    client.disconectToServer();

    return 0;
}

LobbyMenu::LobbyMenu() : playerList_(SERVER_NB_MAX_PLAYERS), lobbyList_(SERVER_NB_MAX_LOBBY){
    ind_ = 0;
    index_ = "";

    for(int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
        for(int j = 0; j  < NB_MAX_JOUEURS; j++) {
            lobbyList_[i].players[j] = new PlayerInfo();
        }
    }
}

LobbyMenu::~LobbyMenu() {
    for(int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
        for(int j = 0; j  < NB_MAX_JOUEURS; j++) {
            delete lobbyList_[i].players[j];
        }
    }
}
