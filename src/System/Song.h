//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_SONG_H
#define MUSICMECH_CLIENT_SONG_H

#include <SFML/Audio.hpp>
#include <string>
#include <map>

#include "../Mechanics/Mechanic.h"

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
	std::vector<std::pair<float, float>> checkpoints_;


	int getCheckpoint(float time);
public:
    Song() = default;
	Song(const std::string& osuFile, std::vector<Mechanic*> &mech);
	void play();
	void pause();
	void load(const std::string& osuFile, std::vector<Mechanic*> &mech);
	sf::Time getCurrentTime();
	TIMING_POINT getCurrentBeat(int ms);



	float getBeatOffset(int ms);
    float getBeatLength(int ms);
	float getCurrentBeatOffset();
	float getCurrentBeatLength();

	float getCumulativeNBeats(int ms);

	void setTime(sf::Time time);

	void addCheckpoint(float time, float beat);
	void resetCheckpoints();
	std::pair<float, float> getCurrentCheckpoint(float time);
    std::pair<float, float> getPreviousCheckpoint(float time);
    std::pair<float, float> getNextCheckpoint(float time);
};

#endif //MUSICMECH_CLIENT_SONG_H
