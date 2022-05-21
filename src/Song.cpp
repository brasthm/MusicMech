//
// Created by cyril on 21/05/2022.
//

#include "Song.h"

#include <iostream>
#include <fstream>

#include "Utils.h"

#include "Tower.h"

/*
std::wstringstream readFile(std::string filename)
{
    std::wifstream wif(filename);
    wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    std::wstringstream wss;
    wss << wif.rdbuf();
    return wss;
}*/



Song::Song(std::string osuFile, std::vector<Mechanic*> &mechs) {
    //char line_buffer[BUFSIZ]; /* BUFSIZ is defined if you include stdio.h */

   /* FILE* infile = fopen(osuFile.c_str(), "r");
    if (!infile) {
        printf("\nFile '%s' not found\n", osuFile);
    }
    printf("\nReading %s:\n\n", osuFile);

    int line_number = 0;
    std::string section = "Format";
    while (fgets(line_buffer, sizeof(line_buffer), infile)) {
        std::string line = line_buffer;
        
        if (line_buffer[0] == '[') {
            section = line_buffer;
        }
        ++line_number;
        // note that the newline is in the buffer
        printf("%d: %s", line_number, line_buffer);
    }*/

    std::ifstream file(osuFile);

    if (!file.is_open()) {
        std::cout << "Erreur" << std::endl;
    }
    bool readnow = false;
    
    if (music_.openFromFile("D:\\_raphael\\Programation\\Cpp\\MusicMech\\Beatmaps\\461509 Marshmello - Alone\\audio.ogg"))
        std::cout << "hmmm" << std::endl;

    while (!file.eof()) {

       

        std::string line;
        std::getline(file, line);

        if (line == "[HitObjects]") {
            readnow = true;
            continue;
        }

        if (readnow) {
            std::cout << line << std::endl;
            std::vector<std::string> words = Utils::split(line, ',');
            if (words.size() != 0) {
                int x, y, time, type;
                x = std::stoi(words[0]);
                y = std::stoi(words[1]);
                time = std::stoi(words[2]);
                type = std::stoi(words[3]);
                std::cout << x << ' ' << y << ' ' << time << ' ' << type << std::endl;

                mechs.emplace_back(new Tower(0.6 * (time - 70) / 142, sf::Vector2f(x, y), 70));
            }
        }
    }
}

void Song::play()
{
    music_.play();
}

sf::Time Song::getCurrentTime()
{
    return music_.getPlayingOffset();
}

