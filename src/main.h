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
static constexpr int NB_MAX_JOUEURS = 8;
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


static constexpr float KEEP_ALIVE_TIMER = 30;

static constexpr float NUMBER_PROFILE = 8;

// Server Info

static const std::string SERVER_NAME = "SYNCHROBEATSERV";
static const std::string SERVER_VERSION = "2.0";
static constexpr int SERVER_NB_MAX_PLAYERS = 100;
static constexpr int SERVER_NB_MAX_LOBBY = 50;
inline sf::IpAddress SERVER_IP = "77.140.124.65"; // Saint-Etienne
//inline sf::IpAddress SERVER_IP = "78.241.228.179"; // Montluçon
//inline sf::IpAddress SERVER_IP = "127.0.0.1"; // Localhost
static constexpr unsigned short SERVER_ADMIN_PORT = 41110;
static constexpr unsigned short SERVER_CONNECT_PORT = 41101;
static constexpr unsigned short SERVER_GAME_PORT = 41102;
static constexpr unsigned short SERVER_LOGIN_PORT = 41103;
static constexpr int SERVER_TICK_MS = 200;
static constexpr int CLIENT_TICK_MS = 200;
static constexpr int SERVER_SLEEP = 10;
static constexpr float TRANSITION_DELAY = 0.5;


static constexpr int COLOR_RED = 0xff6392ff;
static constexpr int COLOR_BLUE = 0x5ab1bbff;
static constexpr int COLOR_YELLOW = 0xf7dd72ff;
static constexpr int COLOR_GREEN = 0xa5c882ff;


static constexpr int COLOR_SEMI_RED = 0xff639288;
static constexpr int COLOR_SEMI_BLUE = 0x5ab1bb88;
static constexpr int COLOR_SEMI_YELLOW = 0xf7dd7288;
static constexpr int COLOR_SEMI_GREEN = 0xa5c88288;

// BANNERS
static constexpr int BANNER_EMPTY = 0;
static constexpr int BANNER_NOVICE = 1;
static constexpr int BANNER_BLUE = 2;
static constexpr int BANNER_RED = 3;
static constexpr int BANNER_YELLOW = 4;
static constexpr int BANNER_GREEN = 5;

class  BannerData {
public:
	BannerData(std::string n, std::string p, std::string sh, std::string tsh) : name(n), path(p), shader(sh), textShader(tsh) {};
	std::string name, path;
	std::string shader, textShader;
};

static const std::vector<BannerData> BANNERS = {
	BannerData("", "empty.png", "", ""),
	BannerData("Novice", "novice.png", "", ""),
	BannerData("Synchro blue", "blue.png", "", ""),
	BannerData("Synchro red", "red.png", "", ""),
	BannerData("Synchro yellow", "yellow.png", "", ""),
	BannerData("Synchro green", "green.png", "", ""),
	BannerData("Test shader", "green.png", "Shader/rainbowborder.frag", ""),
	BannerData("Text shader", "green.png", "", "Shader/rainbow.frag"),
	BannerData("Both shader", "green.png", "Shader/flash.frag", "Shader/rainbow.frag")
};

// TITLE
static constexpr int TITLE_EMPTY = 0;
static constexpr int TITLE_EAGER = 1;
static constexpr int TITLE_CLEARER = 2;
static constexpr int TITLE_PANICKED = 3;
static constexpr int TITLE_CONTROLLER = 4;
static constexpr int TITLE_EARLY = 5;
static constexpr int TITLE_YELLOW = 6;
static constexpr int TITLE_LAG = 7;
static constexpr int TITLE_COMPLETIONIST = 8;
static constexpr int TITLE_PROTAGONIST = 9;
static constexpr int TITLE_TEAMPLAYER = 10;
static constexpr int TITLE_NOVICE = 11;

static const std::vector<std::string> TITLES = {
	"",
	"Eager for more",
	"The Serial Clearer",
	"\"I panicked\"",
	"\"It's the controller's fault\"",
	"\"I'm not early, I anticipate\"",
	"\"I blame this on yellow\"",
	"\"It's lag\"",
	"The Completionist",
	"The Protagonist",
	"The Teamplayer",
	"Experienced novice"
};

static constexpr int STATISTIC_DISTANCE = 0;
static constexpr int STATISTIC_TARGET = 1;
static constexpr int STATISTIC_STILL = 2;
static constexpr int STATISTIC_FAILED = 3;
static constexpr int STATISTIC_GREED = 4;
static constexpr int STATISTIC_INSHARE = 5;

static constexpr int TIMESTAMPS_FAILED = 0;


#endif //MUSICMECH_SERVER_MAIN_H
