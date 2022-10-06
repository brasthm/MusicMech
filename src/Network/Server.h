//
// Created by cyril on 13/05/2022.
//

#ifndef MUSICMECH_SERVER_SERVER_H
#define MUSICMECH_SERVER_SERVER_H

#include "UDP_Port.h"
#include "TCP_Socket.h"
#include "PlayerInfo.h"
#include "Lobby.h"
#include "../System/SongData.h"
#include "../main.h"

#include <vector>
#include <map>



class Server {
private:
    UDP_Port admin_, game_, login_;
    std::vector<PlayerInfo> players_;
    std::vector<Lobby> lobbies_;
    sf::Int32 serverSeed_;
    sf::Clock serverTick_;

    SongDatabase songs_;

    std::vector<TCP_Socket*> clients_;
    sf::TcpListener connector_;
    bool accepting_ = false, creating_ = false, closing_ = false;

    sf::SocketSelector selector_;
protected:
    void monitorAdminCommand();
    void monitorPlayerData();
    void monitorLoginUDP();
    void monitorClient(int i);
    void updateLobbies(sf::Time elapsed);
    void sendPlayerData();
    void startGames();


    void accept(TCP_Socket* newEntry);
    void cleanup();


    bool checkConnected(sf::IpAddress address, unsigned short port);
    int findConnected(sf::IpAddress address, unsigned short port);
    int findUDPConnected(sf::IpAddress address, sf::Uint32 port);
    int findFistAvailableConnected();
    int findLobbyContainingPlayer(sf::IpAddress address, unsigned short port);

    void sendRoomLobbyNotif(int index, sf::Uint8 state, sf::Uint8 param, sf::Uint64 timestamp = 0);

public:
    Server();
    ~Server() = default;

    void run();

};


#endif //MUSICMECH_SERVER_SERVER_H
