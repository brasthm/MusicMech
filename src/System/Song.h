//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_SONG_H
#define MUSICMECH_CLIENT_SONG_H

#include <SFML/Audio.hpp>
#include <string>
#include <map>

#include "../Mechanics/Mechanic.h"


class Song {
private:
    std::vector<std::pair<float, float>> timingPoints_;
	std::vector<std::pair<float, float>>::iterator currentTimingPoint_;
	std::vector<std::pair<float, float>> checkpoints_;
    std::string audioFile_;


	int getCheckpoint(float time);
public:
    Song();
	~Song();
	void load(const std::string& osuFile, sf::Music *music, std::vector<Mechanic*> &mech, Arena* arena);
    std::pair<float, float> getCurrentBeat(float ms);


	void save(const std::string& file, const std::vector<Mechanic*> &mech, Arena &arena);



	float getBeatOffset(float ms);
    float getBeatLength(float ms);
	float getCurrentBeatOffset(sf::Time current);
	float getCurrentBeatLength(sf::Time current);

	float getCumulativeNBeats(float ms);

	void addCheckpoint(float time, float beat);
	void resetCheckpoints();
	std::pair<float, float> getCurrentCheckpoint(float time);
    std::pair<float, float> getPreviousCheckpoint(float time);
    std::pair<float, float> getNextCheckpoint(float time);
};

#endif //MUSICMECH_CLIENT_SONG_H
