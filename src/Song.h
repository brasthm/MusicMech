//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_SONG_H
#define MUSICMECH_CLIENT_SONG_H

#include <SFML/Audio.hpp>
#include <string>

#include "Mechanic.h"

struct TIMING_POINT {
	float beatOffset;
	float beatLength;

	TIMING_POINT() = default;
    inline TIMING_POINT(float bOffset, float bLength) { beatLength = bLength; beatOffset = bOffset;};
};

class Song {
private:
	sf::Music music_;
	std::vector<TIMING_POINT> timingPoints_;
	std::vector<TIMING_POINT>::iterator currentTimingPoint_;
public:
	Song(std::string osuFile, std::vector<Mechanic*> &mech);
	void play();
	sf::Time getCurrentTime();
	TIMING_POINT getCurrentBeat(int ms);
	int getCurrentBeatOffset();
	float getCurrentBeatLength();

    int getBeatOffset(int ms);
    float getBeatLength(int ms);
};

#endif //MUSICMECH_CLIENT_SONG_H
