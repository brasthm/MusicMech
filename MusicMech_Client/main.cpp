#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "../src/Client.h"
#include "../src/Game.h"

int main() {
    std::string cmd;

    Client c;

    while(cmd != "exit") {

        std::cout << ">> ";
        std::getline(std::cin, cmd);

        if(cmd == "connect") {
            if(c.connectToServer())
                std::cout << "Connected" << std::endl;
            else
                std::cout << "Connection failed" << std::endl;
        }
        else if(cmd == "disconnect") {
            if(c.disconectToServer())
                std::cout << "Disconnected" << std::endl;
            else
                std::cout << "Disconnection failed" << std::endl;
        }
        else if(cmd == "run") {
            sf::RenderWindow mainWindow(sf::VideoMode(800,600), "MusicMech");
            Game g(mainWindow, &c);
            g.run();
        }
        else if(cmd != "exit") {
            c.sendCommand(cmd);
        }
    }
    return 0;
}
