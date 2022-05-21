//
// Created by cyril on 16/05/2022.
//

#ifndef MUSICMECH_CLIENT_CLIENT_H
#define MUSICMECH_CLIENT_CLIENT_H

#include "UDP_Port.h"
#include "Joueur.h"
#include <vector>

class Client {
private:
    UDP_Port clientSocket_;
    sf::Int32 clientSeed_, challengeResponse_, index_;
    sf::Uint16 packetID_;
public:
    Client();
    bool connectToServer();
    bool disconectToServer();
    void sendCommand(const std::string& cmd);
    void sendPlayerData(sf::Int32 x, sf::Int32 y);
    int getIndex() const {return index_;};
    void updateFromServerPlayerPosition(std::vector<Joueur> &joueurs);

};


#endif //MUSICMECH_CLIENT_CLIENT_H
