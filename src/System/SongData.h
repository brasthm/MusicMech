#ifndef MUSICMECH_SERVER_SONGDATA_H
#define MUSICMECH_SERVER_SONGDATA_H


#include <string>
#include <vector>
#include <fstream>

#include <SFML/Audio.hpp>


struct SongVariant {
	std::string mmpath;    // chemin relatif du .mm
	std::string label;     // "Classique", "Expert"…
	std::string difficulty;// Difficulty: du .mm
	std::string nbPlayers; // Players: du .mm
};


class SongData {
public:
	std::string name, artist, image, vignette, id, songpath;
	int preview;
	std::vector<SongVariant> variants;
};

class SongDatabase {
private:
	std::vector<SongData> songs_;
	std::ifstream file_;
	sf::Music music_;

	int selected_, selectedVariant_;
public:
	SongDatabase();
	SongData getSelectedSong();
	SongVariant getSelectedVariant();
	void play();
	void stop();
	int size();
	int getSelected();
	int getIndexVariant();
	int sizeVariant(int song);
	void setSelected(int selected, int variant);
	void setSelectedById(const std::string& id, int variant);
	SongData getSong(int i);
	SongVariant getVariant(int song, int var);
	void setSong(int i);
	bool isPlaying();
	std::string getCurentNbPlayers();
	std::string getSelectedPath();
	std::string getCurrentId();

	void setVariant(std::string name);
};


#endif