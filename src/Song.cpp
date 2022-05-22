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
                    float beatOffset = std::stoi(words[0]);
                    float beatLength = std::stof(words[1]);
                    int meter        = std::stoi(words[2]);
                    int uninherited  = std::stoi(words[6]);

                    if (uninherited == 1)
                    {
                        std::cout << "  offset: " << beatOffset << ", ms per beat : " << beatLength << " (" << 60 / (beatLength / 1000) << " bpm)" << std::endl;
                        timingPoints_.push_back(TIMING_POINT(beatOffset, beatLength));
                        currentTimingPoint_ = timingPoints_.begin();
                    }
                }
                else if (*parsing == "[HitObjects]") {
                    int x, y, time, type;
                    x = std::stoi(words[0]);
                    y = std::stoi(words[1]);
                    time = std::stoi(words[2]);
                    type = std::stoi(words[3]);
                    //std::cout << x << ' ' << y << ' ' << time << ' ' << type << std::endl;

                    mechs.emplace_back(new Tower((int)getCumulativeNBeats(time), sf::Vector2f(x, y), 70));
                    std::cout << mechs.back()->toString() << std::endl;
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

TIMING_POINT Song::getCurrentBeat(int ms)
{
    while (currentTimingPoint_ != timingPoints_.begin()  &&  ms < currentTimingPoint_->beatOffset)
        currentTimingPoint_--;

    auto nextTimingPoint = std::next(currentTimingPoint_);
    while (nextTimingPoint != timingPoints_.end()  &&  ms >= nextTimingPoint->beatOffset) {
        currentTimingPoint_++;
        nextTimingPoint++;
    }

    return *currentTimingPoint_;
}

float Song::getBeatOffset(int ms) {
    return (float)getCurrentBeat(ms).beatOffset;
}

float Song::getBeatLength(int ms) {
    return getCurrentBeat(ms).beatLength;
}

float Song::getCurrentBeatOffset()
{
    return getBeatOffset(getCurrentTime().asMilliseconds());
}

float Song::getCurrentBeatLength()
{
    return getBeatLength(getCurrentTime().asMilliseconds());
}

float Song::getCumulativeNBeats(int ms) {
    float nBeats = 0;
    std::vector<TIMING_POINT>::iterator t1, t2;
    t1 = timingPoints_.begin();
    t2 = std::next(t1);
    //std::cout << timingPoints_.size() << " ";

    while (t2 != timingPoints_.end() && ms > t2->beatOffset) {

        nBeats += (t2->beatOffset - t1->beatOffset) / t1->beatLength;

        t1++;
        t2++;
    }

    nBeats += (ms - t1->beatOffset) / t1->beatLength;

    //std::cout << std::endl;
    return nBeats;
}
