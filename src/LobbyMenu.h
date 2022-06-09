//
// Created by cyril on 01/06/2022.
//

#ifndef MUSICMECH_CLIENT_LOBBYMENU_H
#define MUSICMECH_CLIENT_LOBBYMENU_H

#include "Lobby.h"
#include "PlayerInfo.h"
#include "Client.h"
#include "Game.h"

class LobbyMenu {
private:
    std::vector<PlayerInfo> playerList_;
    std::vector<Lobby> lobbyList_;
    std::string index_;
    int ind_;

public:
    LobbyMenu();
    ~LobbyMenu();
    int run(sf::RenderWindow &window, Game &game, Client &client);

};


#endif //MUSICMECH_CLIENT_LOBBYMENU_H
