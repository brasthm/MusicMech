#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <climits>

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
            settings.antialiasingLevel = 8;
            sf::RenderWindow mainWindow(sf::VideoMode(WIDOW_WIDTH, WIDOW_HEIGHT), "Sychrobeat", sf::Style::Fullscreen, settings);
            mainWindow.setFramerateLimit(60);
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
            g.load("a");
            g.save("output.txt");

        }
        else if (cmd == "limit") {
            std::cout << "CHAR_BIT    :  " << CHAR_BIT << std::endl;
            std::cout << "CHAR_MAX    :  " << CHAR_MAX << std::endl;
            std::cout << "CHAR_MIN    :  " << CHAR_MIN << std::endl;
            std::cout << "INT_MAX     :  " << INT_MAX << std::endl;
            std::cout << "INT_MIN     :  " << INT_MIN << std::endl;
            std::cout << "LONG_MAX    :  " <<  (long)LONG_MAX << std::endl;
            std::cout << "LONG_MIN    :  " <<  (long)LONG_MIN << std::endl;
            std::cout << "SCHAR_MAX   :  " << SCHAR_MAX << std::endl;
            std::cout << "SCHAR_MIN   :  " << SCHAR_MIN << std::endl;
            std::cout << "SHRT_MAX    :  " << SHRT_MAX << std::endl;
            std::cout << "SHRT_MIN    :  " << SHRT_MIN << std::endl;
            std::cout << "UCHAR_MAX   :  " << UCHAR_MAX << std::endl;
            std::cout << "UINT_MAX    :  " << (unsigned int)UINT_MAX << std::endl;
            std::cout << "ULONG_MAX   :  " <<  (unsigned long)ULONG_MAX << std::endl;
            std::cout << "USHRT_MAX   :  " << (unsigned short)USHRT_MAX << std::endl;
        }
        else if (cmd == "port") {
            std::cout << c.getUdpPort() << std::endl;
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
    mainWindow.setFramerateLimit(60);
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
