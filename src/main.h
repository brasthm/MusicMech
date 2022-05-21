//
// Created by cyril on 13/05/2022.
//

#ifndef MUSICMECH_SERVER_MAIN_H
#define MUSICMECH_SERVER_MAIN_H


#include <string>
#include <SFML/Network.hpp>

// Général

static constexpr float PI = 3.14159265f;

static constexpr int TIMOUT_TIME = 5;
static constexpr int NB_MAX_JOUEURS = 16;

// Server Info

static const std::string SERVER_NAME = "MATCHMECHSERV";
static const std::string SERVER_VERSION = "1.0";
static constexpr int SERVER_NB_MAX_PLAYERS = 16;
static const sf::IpAddress SERVER_IP = "192.168.0.173";
static constexpr unsigned short SERVER_ADMIN_PORT = 54000;
static constexpr unsigned short SERVER_CONNECT_PORT = 54001;
static constexpr unsigned short SERVER_GAME_PORT = 54002;
static constexpr int SERVER_TICK_MS = 100;
static constexpr int CLIENT_TICK_MS = 20;


#endif //MUSICMECH_SERVER_MAIN_H
