//
// Created by cyril on 13/05/2022.
//

#ifndef MUSICMECH_SERVER_MAIN_H
#define MUSICMECH_SERVER_MAIN_H


#include <string>
#include <SFML/Network.hpp>

// Général


inline bool IS_SERVER = false;
inline bool GOD_MODE = true;

static constexpr float PI = 3.14159265f;
static constexpr float SQRT2 = 1.41421356237f;

static constexpr int TIMOUT_TIME = 5;
static constexpr int NB_MAX_JOUEURS = 4;
static constexpr int NB_MAX_TOTEM = 8;

static constexpr float BASE_PLAYER_RADIUS = 20;
static constexpr float BASE_TOTEM_RADIUS = 10;

static constexpr int NB_MAX_SOUND = 50;
static constexpr int NB_MAX_MUSIC = 5;

static constexpr int ARENA_WIDTH = 1000;
static constexpr int ARENA_HEIGHT = 1000;

static constexpr int WIDOW_WIDTH = 1920;
static constexpr int WIDOW_HEIGHT = 1080;


static constexpr float JOYSTICK_DEADZONE = 15;
static constexpr float JOYSTICK_MAXZONE = 85;

// Server Info

static const std::string SERVER_NAME = "MATCHMECHSERV";
static const std::string SERVER_VERSION = "1.0";
static constexpr int SERVER_NB_MAX_PLAYERS = 100;
static constexpr int SERVER_NB_MAX_LOBBY = 50;
//static const sf::IpAddress SERVER_IP = "77.140.124.65";
inline sf::IpAddress SERVER_IP = "78.241.228.179";
//static const sf::IpAddress SERVER_IP = "127.0.0.1";
static constexpr unsigned short SERVER_ADMIN_PORT = 5000;
static constexpr unsigned short SERVER_CONNECT_PORT = 5001;
static constexpr unsigned short SERVER_GAME_PORT = 5002;
static constexpr unsigned short SERVER_LOBBY_PORT = 5003;
static constexpr int SERVER_TICK_MS = 50;
static constexpr int CLIENT_TICK_MS = 50;
static constexpr int SERVER_SLEEP = 10;


#endif //MUSICMECH_SERVER_MAIN_H
