#ifndef MUSICMECH_SERVER_SONGDATA_H
#define MUSICMECH_SERVER_SONGDATA_H


#include <string>
#include <vector>
#include <fstream>

#include <SFML/Audio.hpp>
#include "Song.h"

class SongData {
public:
	std::string name, artist, image, vignette, id, songpath, mmpath, difficulty;
	int preview;
};

class SongDatabase {
private:
	std::vector<SongData> songs_;
	std::ifstream file_;
	sf::Music music_;

	int selected_;
	std::string mode_;
public:
	SongDatabase();
	SongData getSelectedSong();
	void play();
	void stop();
	int size();
	int getSelected();
	void setSelected(int selected);
	void setSelectedById(const std::string& id);
	SongData getSong(int i);
	void setSong(int i);
	bool isPlaying();
	std::string getMode();
	std::string getSelectedPath();
	void setMode(const std::string &mode);
};


#endif