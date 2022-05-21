//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_SONG_H
#define MUSICMECH_CLIENT_SONG_H

#include <SFML/Audio.hpp>
#include <string>

class Song {
private:
	std::wstringstream readFile(std::string filename);
public:
	Song(std::string osuFile);
};


#endif //MUSICMECH_CLIENT_SONG_H
