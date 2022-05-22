//
// Created by cyril on 21/05/2022.
//

#include "Song.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "Utils.h"
#include "RessourceLoader.h"

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
    
    std::string osuPath = RessourceLoader::getPath(osuFile);

    // open osu file
    std::cout << "opening " << osuPath << std::endl;
    std::ifstream file(osuPath);
    if (!file.is_open()) {
        std::cout << "Error: did not find osu file " << osuPath << std::endl;
        return;
    }

    // parse osu file

    std::vector<std::string> toParse;
    toParse.push_back("AudioFilename:");
    toParse.push_back("[TimingPoints]");
    toParse.push_back("[HitObjects]");
    std::vector<std::string>::iterator parsing = toParse.begin();

    std::string line;
    bool readnow = false;
    
    while (!file.eof()) {
        std::getline(file, line);

        
        if (readnow && line[0] == '[') {
            readnow = false;
            parsing++;
        }

        if (line.rfind(*parsing, 0) == 0)  // if line starts with *parsing
        {
            if (*parsing == "AudioFilename:") {
                std::string audioFile = Utils::trim(Utils::split(line, ':')[1]);
                std::filesystem::path audioPath = std::filesystem::path(osuPath).parent_path() / audioFile;
                if (!music_.openFromFile(audioPath.string()))
                    std::cout << "Error: could not open music file " << audioFile << std::endl;
                parsing++;
            }
            else if (*parsing == "[TimingPoints]" || *parsing == "[HitObjects]") {
                std::cout << "parsing " << *parsing << std::endl;
                readnow = true;
                continue;
            }
        }

        if (readnow) {
            std::vector<std::string> words = Utils::split(line, ',');
            if (words.size() != 0) {
                //std::cout << line << std::endl;

                if (*parsing == "[TimingPoints]") {
                    offset_ = std::stoi(words[0]);
                    msPerBeat_ = std::stof(words[1]);
                    std::cout << "  ms per beat: " << msPerBeat_ << " (" << 60 / (msPerBeat_ / 1000) << " bpm), offset: " << offset_ << std::endl;

                    // for now, ignore everything but the first
                    std::cout << "  skipping other timing points for now..." << std::endl;
                    readnow = false;
                    parsing++;
                }
                else if (*parsing == "[HitObjects]") {
                    int x, y, time, type;
                    x = std::stoi(words[0]);
                    y = std::stoi(words[1]);
                    time = std::stoi(words[2]);
                    type = std::stoi(words[3]);
                    //std::cout << x << ' ' << y << ' ' << time << ' ' << type << std::endl;

                    mechs.emplace_back(new Tower(0.6 * (time - 70) / 142, sf::Vector2f(x, y), 70));
                }
            }
        }
    }
    std::cout << "  converted " << mechs.size() << " hit objects to mechanics" << std::endl;
    std::cout << "beatmap parsed!" << std::endl;
    file.close();
}

void Song::play()
{
    music_.play();
}

sf::Time Song::getCurrentTime()
{
    return music_.getPlayingOffset();
}

float Song::getCurrentMsPerBeat()
{
    return msPerBeat_;
}

int Song::getCurrentOffset()
{
    return offset_;
}

