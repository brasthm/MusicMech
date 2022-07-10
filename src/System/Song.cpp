//
// Created by cyril on 21/05/2022.
//

#include "Song.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "Utils.h"
#include "RessourceLoader.h"

#include "../Mechanics/Spread.h"
#include "../Mechanics/Tether.h"
#include "../Mechanics/ApplyDebuff.h"
#include "../Mechanics/MoveEntity.h"
#include "../Mechanics/ActivateTotem.h"

std::pair<float, float> Song::getCurrentBeat(float ms)
{
    while (currentTimingPoint_ != timingPoints_.begin()  &&  ms < currentTimingPoint_->first)
        currentTimingPoint_--;

    auto nextTimingPoint = std::next(currentTimingPoint_);
    while (nextTimingPoint != timingPoints_.end()  &&  ms >= nextTimingPoint->first) {
        currentTimingPoint_++;
        nextTimingPoint++;
    }

    return *currentTimingPoint_;
}

float Song::getBeatOffset(float ms) {
    return (float)getCurrentBeat(ms).first;
}

float Song::getBeatLength(float ms) {
    return getCurrentBeat(ms).second;
}

float Song::getCurrentBeatOffset(sf::Time current)
{
    return getBeatOffset(current.asMilliseconds());
}

float Song::getCurrentBeatLength(sf::Time current)
{
    return getBeatLength(current.asMilliseconds());
}

float Song::getCumulativeNBeats(float ms) {
    float nBeats = 0;
    std::vector<std::pair<float, float>>::iterator t1, t2;
    t1 = timingPoints_.begin();
    t2 = std::next(t1);
    //std::cout << timingPoints_.size() << " ";

    while (t2 != timingPoints_.end() && ms > t2->first) {

        nBeats += (t2->first - t1->first) / t1->second;

        t1++;
        t2++;
    }

    nBeats += (ms - t1->first) / t1->second;

    //std::cout << std::endl;
    return nBeats;
}


void Song::load(const std::string& osuFile, sf::Music *music, std::vector<Mechanic *> &mechs) {
    std::string osuPath = RessourceLoader::getPath(osuFile);

    // open osu file
    std::cout << "opening " << osuPath << std::endl;
    std::ifstream file(osuPath);
    if (!file.is_open()) {
        std::cout << "Error: did not find osu file " << osuPath << std::endl;
        return;
    }


    timingPoints_.clear();
    checkpoints_.clear();
    for(auto &mech:mechs)
        delete mech;
    mechs.clear();

    // parse osu file

    std::vector<std::string> toParse;
    if(music != nullptr)
        toParse.emplace_back("AudioFilename:");
    toParse.emplace_back("[TimingPoints]");
    toParse.emplace_back("[Checkpoints]");
    toParse.emplace_back("[Objects]");
    auto parsing = toParse.begin();

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
                if(music != nullptr) {
                    audioFile_ = Utils::trim(Utils::split(line, ':')[1]);
                    std::filesystem::path audioPath = std::filesystem::path(osuPath).parent_path() / audioFile_;
                    if (!music->openFromFile(audioPath.string()))
                        std::cout << "Error: could not open music file " << audioFile_ << std::endl;
                    parsing++;
                }
            }
            else if (*parsing == "[TimingPoints]" || *parsing == "[Objects]" || *parsing == "[Checkpoints]") {
                readnow = true;
                continue;
            }
        }

        if (readnow) {
            std::vector<std::string> words = Utils::split(line, ',');
            if (words.size() != 0 && words[0] != "\r") {
                //std::cout << line << std::endl;

                if (*parsing == "[TimingPoints]") {
                    float beatOffset = std::stof(words[0]);
                    float beatLength = std::stof(words[1]);
                    int uninherited  = std::stoi(words[6]);

                    if (uninherited == 1)
                    {
                        std::cout << "timingpoint" << std::endl;
                        timingPoints_.emplace_back(beatOffset, beatLength);
                        currentTimingPoint_ = timingPoints_.begin();
                    }
                }
                else if (*parsing == "[Checkpoints]") {
                    float timestamp = std::stof(words[0]);
                    float beat = std::stof(words[1]);

                    checkpoints_.emplace_back(timestamp, beat);
                }
                else if (*parsing == "[Objects]") {
                    if(words[0] == "SPREAD") {
                        float beat, active, radius;
                        int nbShare;

                        beat = std::stof(words[1]);
                        nbShare = std::stoi(words[2]);
                        radius = std::stof(words[3]);
                        active = std::stof(words[4]);

                        Target t;

                        t.parse(5, words);
                        mechs.emplace_back(new Spread(beat, radius, nbShare, active, t));
                    }
                    else if(words[0] == "TETHER") {
                        float beat, minDist, active;
                        bool inward, continu;

                        Target t1, t2;

                        beat = std::stof(words[1]);
                        minDist = std::stof(words[2]);
                        active = std::stof(words[3]);

                        inward = std::stoi(words[4]) == 1;
                        continu = std::stoi(words[5]) == 1;

                        int off = t1.parse(6, words);
                        t2.parse(off, words);

                        mechs.emplace_back(new Tether(beat, t1, t2, minDist, active, inward, continu));
                    }
                    else if(words[0] == "MOVE") {
                        float beat, speed;
                        bool isInstant;

                        beat = std::stof(words[1]);
                        speed = std::stof(words[2]);
                        isInstant = std::stoi(words[3]) == 1;

                        Target entity, target;

                        int off = entity.parse(4, words);
                        target.parse(off, words);

                        mechs.emplace_back(new MoveEntity(beat, entity, target, speed, isInstant));
                    }
                    else if(words[0] == "DEBUFF") {
                        float beat, duration;
                        DebuffType debufftype;

                        Target t;

                        beat = std::stof(words[1]);
                        debufftype = static_cast<DebuffType>(std::stoi(words[2]));
                        duration = std::stof(words[3]);
                        t.parse(4, words);

                        mechs.emplace_back(new ApplyDebuff(beat, t, debufftype, duration));
                    }
                    else if(words[0] == "ACTIVATE") {
                        float beat;
                        bool val;
                        Target t;

                        beat = std::stof(words[1]);
                        val = std::stoi(words[2]) == 1;
                        t.parse(3, words);

                        mechs.emplace_back(new ActivateTotem(beat, t, val));
                    }
                }
            }
        }
    }
    file.close();
}


void Song::addCheckpoint(float time, float beat) {
    checkpoints_.emplace_back(time, beat);
}

int Song::getCheckpoint(float time) {
    std::cout << "Checkpoint - "  << checkpoints_.size();
    if(checkpoints_.empty())
        return -1;

    int i = 0;


    while(i < checkpoints_.size() && time > checkpoints_[i].second) {
        i++;
    }

    if(i!=0)
        i--;

    std::cout << " " << i << std::endl;

    return i;
}

std::pair<float, float> Song::getCurrentCheckpoint(float time) {
    int res = getCheckpoint(time);

    if(res == -1)
        return {0,0};

    return checkpoints_[res];
}

std::pair<float, float> Song::getPreviousCheckpoint(float time) {
    int res = getCheckpoint(time);

    if(res == -1)
        return {0,0};

    if(res == 0)
        return checkpoints_[0];

    return checkpoints_[res-1];
}

std::pair<float, float> Song::getNextCheckpoint(float time) {
    int res = getCheckpoint(time);

    if(res == -1)
        return {0,0};

    if(res == checkpoints_.size() - 1)
        return checkpoints_[checkpoints_.size() - 1];

    return checkpoints_[res + 1];
}

void Song::resetCheckpoints() {
    checkpoints_.clear();
}

void Song::save(const std::string& filename, const std::vector<Mechanic *> &mechs) {
    std::ofstream file(filename);

    file << "AudioFilename: " << audioFile_ << std::endl;
    file << "[TimingPoints]" << std::endl;
    for(auto & timingPoint : timingPoints_) {
        file << timingPoint.first << "," << timingPoint.second << ",4,2,1,60,1,0" << std::endl;
    }
    file << "[Checkpoints]" << std::endl;
    for(auto &checkpoint:checkpoints_) {
        file << checkpoint.first << "," << checkpoint.second << std::endl;
    }
    file << "[Objects]" << std::endl;
    for(auto &mech:mechs)
        file << mech->toString() << std::endl;

}

Song::~Song() = default;
Song::Song() = default;
