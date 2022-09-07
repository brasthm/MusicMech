#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <iomanip>

#include "../src/Game.h"
#include "../src/LobbySelection.h"
#include "../src/Title.h"
#include "../src/LobbyMenu.h"
#include "../src/RoomCreation.h"
#include "../src/BeatmapSelection.h"
#include "../src/RoomMenu.h"

#include "../src/System/Song.h"
#include "../src/System/SongData.h"
#include "../src/System/RessourceLoader.h"
#include "../src/Network/Client.h"
#include "../src/Graphics/BackgoundAnimation.h"

int console() {
    std::string cmd, nom;

    Client c(nom);

    while (cmd != "exit") {

        std::cout << ">> ";
        std::cin >> cmd;

        if (cmd == "connect") {
            if (c.connectToServer())
                std::cout << "Connected" << std::endl;
            else
                std::cout << "Connection failed" << std::endl;
        }
        else if (cmd == "disconnect") {
            if (c.disconectToServer())
                std::cout << "Disconnected" << std::endl;
            else
                std::cout << "Disconnection failed" << std::endl;
        }
        else if (cmd == "lc") {
            std::string lobbyname;
            std::cin >> lobbyname;
            if (c.requestLobbyCreation(lobbyname, "0", "4P"))
                std::cout << "Lobby created : " << c.getLobbyIndex() << std::endl;
            else
                std::cout << "Lobby creation failled" << std::endl;
        }
        else if (cmd == "ip") {
            std::string ip;
            std::cin >> ip;

            SERVER_IP = ip;
        }
        else if (cmd == "name") {
            std::string n;
            std::cin >> n;

            c.changeName(n);

        }
        else if (cmd == "ctrlr") {
            sf::RenderWindow mainWindow(sf::VideoMode(WIDOW_WIDTH / 10.f, WIDOW_HEIGHT / 10.f), "Sychrobeat");
            while (mainWindow.isOpen()) {
                sf::Event event{};
                while (mainWindow.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed) {
                        mainWindow.close();
                    }
                    if (event.type == sf::Event::JoystickButtonPressed) {
                        std::cout << "Button " << event.joystickButton.button << std::endl;
                    }
                }

                mainWindow.display();
            }

        }
        else if (cmd == "run") {
            Title t;
            LobbyMenu lm;
            LobbySelection ls;
            SongDatabase sd;
            RoomCreation rc;
            BeatmapSelection bs;
            RoomMenu rm;

            Game g;

            BackgroundAnimation bg;

            sf::Music title;
            title.openFromFile(RessourceLoader::getPath("Music/Hysteric Night Girl.mp3"));
            title.setVolume(10);
            title.setLoop(true);

            sf::ContextSettings settings;
            settings.antialiasingLevel = 16;
            sf::RenderWindow mainWindow(sf::VideoMode(WIDOW_WIDTH, WIDOW_HEIGHT), "Sychrobeat", sf::Style::Fullscreen, settings);
            int val;
            std::string roomName;
            title.play();
            val = t.run(mainWindow, bg, &c);
            if (val == -1) return 0;
            while (val != -1) {
                roomName = "";
                val = ls.run(mainWindow, bg, &c, sd);
                if (val == 1) {
                    title.pause();
                    while (val != -1) {
                        val = rc.run(mainWindow, bg, &c, sd, roomName);
                        if (val == 1) val = bs.run(mainWindow, bg, &c, &sd);
                        if (val == 2) {
                            while (val != -1) {
                                val = rm.run(mainWindow, bg, &c, &sd, &g, true, val == 1, false);
                                if (val == 1) val = bs.run(mainWindow, bg, &c, &sd);
                                if (val == 2) g.run(mainWindow, &c, true);
                            }
                        }

                    }

                    val = 0;
                    title.play();
                }
                if (val == 2) {
                    title.pause();
                    val = 0;
                    while (val != -1) {
                        val = rm.run(mainWindow, bg, &c, &sd, &g, false, false, val == 2);
                        if (val == 2) g.run(mainWindow, &c, false);
                    }
                    val = 0;
                    title.play();
                }

            }

            //Game g(&c);
            //g.load();
            //lm.run(mainWindow, g, c);
            c.disconectToServer();
        }
        else if (cmd == "save") {
            Game g;
            g.load("");
            g.save("output.txt");

        }
        else if (cmd != "exit") {
            c.sendCommand(cmd);
        }
    }
}


int game()
{
    Client c("");

    Title t;
    LobbyMenu lm;
    LobbySelection ls;
    SongDatabase sd;
    RoomCreation rc;
    BeatmapSelection bs;
    RoomMenu rm;

    Game g;

    BackgroundAnimation bg;

    sf::Music title;
    title.openFromFile(RessourceLoader::getPath("Music/Hysteric Night Girl.mp3"));
    title.setVolume(10);
    title.setLoop(true);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow mainWindow(sf::VideoMode(WIDOW_WIDTH, WIDOW_HEIGHT), "Sychrobeat", sf::Style::Fullscreen, settings);
    int val;
    std::string roomName;
    title.play();
    val = t.run(mainWindow, bg, &c);
    if (val == -1) return 0;
    while (val != -1) {
        roomName = "";
        val = ls.run(mainWindow, bg, &c, sd);
        if (val == 1) {
            title.pause();
            while (val != -1) {
                val = rc.run(mainWindow, bg, &c, sd, roomName);
                if (val == 1) val = bs.run(mainWindow, bg, &c, &sd);
                if (val == 2) {
                    while (val != -1) {
                        val = rm.run(mainWindow, bg, &c, &sd, &g, true, val == 1, false);
                        if (val == 1) val = bs.run(mainWindow, bg, &c, &sd);
                        if (val == 2) g.run(mainWindow, &c, true);
                    }
                }

            }

            val = 0;
            title.play();
        }
        if (val == 2) {
            title.pause();
            val = 0;
            while (val != -1) {
                val = rm.run(mainWindow, bg, &c, &sd, &g, false, false, val == 2);
                if (val == 2) g.run(mainWindow, &c, false);
            }
            val = 0;
            title.play();
        }

    }
    c.disconectToServer();
}

int main() {
    
    console();
    //game();
    return 0;
}
