//
// Created by cyril on 16/05/2022.
//

#ifndef MUSICMECH_CLIENT_CLIENT_H
#define MUSICMECH_CLIENT_CLIENT_H

#include "UDP_Port.h"
#include "../Entity/Joueur.h"
#include "../RoomStatus.h"
#include "../Entity/EntityManager.h"
#include "Lobby.h"
#include <vector>

class RoomStatus;

class Client {
private:
    std::string name_;
    UDP_Port udpSocket_;
    sf::TcpSocket tcpSocket_;
    sf::Int32 clientSeed_, challengeResponse_, index_;
    sf::Uint32 playerID_;
    sf::Uint16 packetID_;
    std::vector<Lobby> lobbyList_;
    std::string lobbyIndex_;
    int lobbyInd_, playerIndex_, pingIndex_;
    sf::Int64 offset_;
    sf::Uint64 startTime_;
    std::vector<sf::Int64> ping_;
    float serverBeat_, position_;
    bool godMode_;
    sf::Clock keepAliveTimer_;
public:
    Client(std::string name = "");
    ~Client();
    bool connectToServer();
    bool disconectToServer();
    void sendCommand(const std::string& cmd);
    void sendPlayerData(sf::Int32 x, sf::Int32 y);
    int getIndex() const {return index_;};
    int updateFromServerPlayerPosition(std::vector<Joueur> &joueurs, std::pair<float, float> &checkpoint, EntityManager& em);

    void changeName(const std::string& name);

    bool requestLobbyCreation(const std::string& name, const std::string& beatmap, const std::string& mode);
    bool requestLobbyJoin(const std::string& lobbyIndex);
    bool requestLobbyDisconnect();
    bool requestLobbyList();
    bool requestLobbyInfo(const std::string& lobbyIndex);
    bool requestLaunchGame();
    bool sendEndGame();
    bool sendPauseGame();
    bool sendResumeGame();
    bool sendReady(sf::Uint32 color);
    bool requestBeatmapChange(const std::string& beatmap, const std::string& mode);
    bool requestPing();
    bool requestRoomStatus(RoomStatus *status, EntityManager& em, const std::string& lobbyIndex = "");

    bool monitorLobby(int &state, EntityManager& em);

    void fetchRandomSequence(sf::Packet& p, EntityManager& em);

    bool waitToStart();


    std::string getLobbyIndex();
    Lobby& getCurrentLobby();

    Lobby& getLobby(int i);

    int getPlayerIndex();
    float getServerBeat();
    sf::Int64 getPing();
    float getPosition();
    unsigned short getUdpPort();
    bool getGodMode();

    bool keepAlive();

};

sf::Socket::Status receiveWithTimeout(sf::TcpSocket& socket, sf::Packet& packet, sf::Time timeout = sf::seconds(5.f));


#endif //MUSICMECH_CLIENT_CLIENT_H
