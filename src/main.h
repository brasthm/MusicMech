//
// Created by cyril on 13/05/2022.
//

#ifndef MUSICMECH_SERVER_MAIN_H
#define MUSICMECH_SERVER_MAIN_H


#include <string>
#include <SFML/Network.hpp>

// Général

static constexpr float PI = 3.14159265f;
static constexpr float SQRT2 = 1.41421356237f;

static constexpr int TIMOUT_TIME = 5;
static constexpr int NB_MAX_JOUEURS = 2;

static constexpr float BASE_PLAYER_RADIUS = 20;

static constexpr int NB_MAX_SOUND = 50;
static constexpr int NB_MAX_MUSIC = 5;

// Server Info

static const std::string SERVER_NAME = "MATCHMECHSERV";
static const std::string SERVER_VERSION = "1.0";
static constexpr int SERVER_NB_MAX_PLAYERS = 100;
static constexpr int SERVER_NB_MAX_LOBBY = 100;
static const sf::IpAddress SERVER_IP = "127.0.0.1";
static constexpr unsigned short SERVER_ADMIN_PORT = 54000;
static constexpr unsigned short SERVER_CONNECT_PORT = 54001;
static constexpr unsigned short SERVER_GAME_PORT = 54002;
static constexpr unsigned short SERVER_LOBBY_PORT = 54003;
static constexpr int SERVER_TICK_MS = 100;
static constexpr int CLIENT_TICK_MS = 20;
static constexpr int SERVER_SLEEP = 10;


#endif //MUSICMECH_SERVER_MAIN_H
