//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_SONG_H
#define MUSICMECH_CLIENT_SONG_H

#include <SFML/Audio.hpp>
#include <string>

#include "Mechanic.h"

class Song {
private:
	sf::Music music_;
	float msPerBeat_;
	int offset_;
public:
	Song(std::string osuFile, std::vector<Mechanic*> &mech);
	void play();
	sf::Time getCurrentTime();
	float getCurrentMsPerBeat();
	int getCurrentOffset();
};

#endif //MUSICMECH_CLIENT_SONG_H
