#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <iomanip>

#include "../src/Client.h"
#include "../src/Game.h"
#include "../src/Song.h"
#include "../src/LobbyMenu.h"

int main() {
    std::string cmd, nom;

    std::cout << "Pseudo : ";
    std::cin >> nom;

    Client c(nom);

    while(cmd != "exit") {

        std::cout << ">> ";
        std::cin >> cmd;

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
        else if(cmd == "lc") {
            std::string lobbyname, lobbyid;
            std::cin >> lobbyname;
            if(c.requestLobbyCreation(lobbyid, lobbyname))
                std::cout << "Lobby created : " << lobbyid << std::endl;
            else
                std::cout << "Lobby creation failled" << std::endl;
        }
        else if(cmd == "lj") {
            std::string lobbyid;
            std::cin >> lobbyid;

            //c.requestLobbyJoin(lobbyid);
        }
        else if(cmd == "ld") {
            std::string lobbyid;
            std::cin >> lobbyid;

            //c.requestLobbyDisconnect(lobbyid);
        }
        else if(cmd == "lroom") {
            std::string lobbyid;
            std::cin >> lobbyid;

            Lobby l;

            if(c.requestLobbyInfo(l, lobbyid)) {
                std::cout << l.name <<  " : " << (int)l.nbIn << "/" << (int)l.limit << std::endl;
                for(int i = 0; i < NB_MAX_JOUEURS; i++)
                    std::cout << "    " << l.players[i]->name << std::endl;
            }
            else
                std::cout << "Erreur" << std::endl;

            for(int i = 0; i < NB_MAX_JOUEURS; i++)
                delete l.players[i];
        }
        else if(cmd == "llist") {
            std::vector<Lobby> lobbylist(SERVER_NB_MAX_LOBBY);

            if(c.requestLobbyList(lobbylist)) {
                std::cout << "|        ID |         Player |                               Name |      |" << std::endl;
                std::cout << "|------------------------------------------------------------------------|" << std::endl;
                for(int i = 0; i < SERVER_NB_MAX_LOBBY; i++) {
                    if(lobbylist[i].status != LobbyStatus::LOBBY_AVAILABLE) {
                        std::cout << "|" << std::setw(10) << lobbylist[i].id << " ";
                        std::cout << "|" << std::setw(15) << lobbylist[i].players[0]->name << " ";
                        std::cout << "|" << std::setw(35) << lobbylist[i].name << " ";
                        std::string sortie = std::to_string(lobbylist[i].nbIn) + "/" + std::to_string(lobbylist[i].limit);
                        std::cout << "|" << std::setw(5) << sortie << " |" << std::endl;
                    }
                }
            }

            for(int i=0; i < SERVER_NB_MAX_LOBBY; i++) {
                for(int j = 0; j < NB_MAX_JOUEURS; j++) {
                    delete lobbylist[i].players[j];
                }
            }
        }
        else if(cmd == "run") {
            LobbyMenu lm;
            sf::ContextSettings settings;
            settings.antialiasingLevel = 8;
            sf::RenderWindow mainWindow(sf::VideoMode(800,600), "MusicMech", sf::Style::Default, settings);
            Game g(&c);
            g.load();
            lm.run(mainWindow, g, c);

        }
        else if (cmd == "load") {
            std::vector<Mechanic*> mechanicList;
            Song song = Song("Beatmaps/546820 YUC'e - Future Candy/YUC'e - Future Candy (Nathan) [Insane].osu", mechanicList);
            song.play();
            while (true) {
                std::cout << song.getCurrentBeatOffset() << " " << song.getCurrentBeatLength() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        else if(cmd != "exit") {
            c.sendCommand(cmd);
        }
    }
    return 0;
}
