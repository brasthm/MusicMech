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
#include "../Mechanics/Cone.h"
#include "../Mechanics/Donut.h"
#include "../Mechanics/NopeZone.h"
#include "../Mechanics/ActivateTotem.h"
#include "../Mechanics/MoveEntity.h"
#include "../Mechanics/ApplyDebuff.h"
#include "../Mechanics/AddArena.h"
#include "../Mechanics/ZoomArena.h"
#include "../Mechanics/RotateArena.h"
#include "../Mechanics/MoveArena.h"
#include "../Mechanics/SnapArena.h"
#include "../Mechanics/RemoveArena.h"
#include "../Mechanics/DisplayImage.h"
#include "../Mechanics/ClearArenaa.h"
#include "../Mechanics/EndMap.h"


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


void Song::load(const std::string& osuFile, sf::Music *music, std::vector<Mechanic *> &mechs, Arena* arena) {
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
    if (arena != nullptr)
        arena->clear();

    // parse osu file

    std::vector<std::string> toParse;
    if(music != nullptr)
        toParse.emplace_back("AudioFilename:");
    toParse.emplace_back("[Arena]");
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
            else if (*parsing == "[Arena]" || *parsing == "[TimingPoints]" || *parsing == "[Objects]" 
                || *parsing == "[Checkpoints]") {
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
                    int uninherited = std::stoi(words[6]);

                    if (uninherited == 1)
                    {
                        std::cout << "timingpoint" << std::endl;
                        timingPoints_.emplace_back(beatOffset, beatLength);
                        currentTimingPoint_ = timingPoints_.begin();
                    }
                }
                else if (*parsing == "[Arena]"){
                    if(arena != nullptr)
                        arena->addRect(std::stof(words[0]), std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
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
                        sf::Uint32 color;

                        beat = std::stof(words[1]);
                        val = std::stoi(words[2]) == 1;
                        color = std::stoul(words[3]);
                        t.parse(4, words);

                        mechs.emplace_back(new ActivateTotem(beat, t, val, color));
                    }
                    else if (words[0] == "CONE") {
                        float beat, active, width, distance;
                        int nbShare;

                        beat = std::stof(words[1]);
                        nbShare = std::stoi(words[2]);
                        width = std::stof(words[3]);
                        distance = std::stof(words[4]);
                        active = std::stof(words[5]);

                        Target t1, t2;

                        int off = t1.parse(6, words);
                        t2.parse(off, words);

                        mechs.emplace_back(new Cone(beat, width, distance, nbShare, active, t1, t2));
                    }
                    else if (words[0] == "DONUT") {
                        float beat, active, minDist, maxDist;
                        int nbShare;

                        beat = std::stof(words[1]);
                        nbShare = std::stoi(words[2]);
                        minDist = std::stof(words[3]);
                        maxDist = std::stof(words[4]);
                        active = std::stof(words[5]);

                        Target t;

                        t.parse(6, words);

                        mechs.emplace_back(new Donut(beat, minDist, maxDist, nbShare, active, t));
                    }
                    else if (words[0] == "NOPEZONE") {
                        float beat, active, width, height;
                        int nbShare;

                        beat = std::stof(words[1]);
                        nbShare = std::stoi(words[2]);
                        width = std::stof(words[3]);
                        height = std::stof(words[4]);
                        active = std::stof(words[5]);

                        Target t;

                        t.parse(6, words);

                        mechs.emplace_back(new NopeZone(beat, width, height, nbShare, active, t));
                    }
                    else if(words[0] == "MOVEARENA") {
                        float beat, speed;
                        Target t;

                        beat = std::stof(words[1]);
                        speed = std::stof(words[2]);
                        t.parse(3, words);

                        mechs.emplace_back(new MoveArena(beat, t, speed));
                    }
                    else if (words[0] == "REMOVEARENA") {
                        float beat, index;

                        beat = std::stof(words[1]);
                        index = std::stof(words[2]);

                        mechs.emplace_back(new RemoveArena(beat, index));
                    }
                    else if (words[0] == "ROTATEARENA") {
                        float beat, angle, speed;

                        beat = std::stof(words[1]);
                        angle = std::stof(words[2]);
                        speed = std::stof(words[3]);

                        mechs.emplace_back(new RotateArena(beat, angle, speed));
                    }
                    else if (words[0] == "SNAPARENA") {
                        float beat, activate;

                        Target t;

                        beat = std::stof(words[1]);
                        activate = std::stof(words[2]);
                        t.parse(3, words);

                        mechs.emplace_back(new SnapArena(beat, activate, t));
                    }
                    else if (words[0] == "ZOOMARENA") {
                        float beat, val, speed;

                        beat = std::stof(words[1]);
                        val = std::stof(words[2]);
                        speed = std::stof(words[3]);

                        mechs.emplace_back(new ZoomArena(beat, val, speed));
                    }
                    else if (words[0] == "DISPLAYIMAGE") {
                        float beat, active;
                        std::string path;

                        beat = std::stof(words[1]);
                        path = words[2];
                        active = std::stoi(words[3]);

                        Target t;
                        t.parse(4, words);

                        mechs.emplace_back(new DisplayImage(beat, path, active, t));
                    }
                    else if (words[0] == "ADDARENA") {
                        float beat, ww, hh, xx, yy;

                        beat = std::stof(words[1]);
                        xx = std::stof(words[2]);
                        yy = std::stof(words[3]);
                        ww = std::stof(words[4]);
                        hh = std::stof(words[5]);

                        mechs.emplace_back(new AddArena(beat, xx, yy, ww, hh));
                    }
                    else if (words[0] == "CLEARARENA") {
                        float beat;

                        beat = std::stof(words[1]);

                        mechs.emplace_back(new ClearArena(beat));
                    }
                    else if (words[0] == "ENDMAP") {
                    float beat;

                    beat = std::stof(words[1]);

                    mechs.emplace_back(new EndMap(beat));
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
    if (checkpoints_.empty()) {
        return -1;
    }

    int i = 0;


    while(i < checkpoints_.size() && time > checkpoints_[i].second) {
        i++;
    }

    if(i!=0)
        i--;

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

std::pair<float, float> Song::getIndexCheckpoint(int section)
{
    return checkpoints_[section];
}

int Song::getMaxCheckpoint()
{
    return checkpoints_.size();
}

float Song::getEndBeat()
{
    return endBeat_;
}

int Song::getSectionPourcentage(float beat, int section)
{
    if (section == -1)
        return 0;

    float d1 = checkpoints_[section].second;
    float d2;
    if (section + 1 == checkpoints_.size()) {
        d2 = endBeat_;
    }
    else {
        d2 = checkpoints_[section + 1].second;
    }

    int res = (beat - d1) / (d2 - d1) * 100 + 0.5f;

    if (res < 0)
        res = 0;
    if (res >= 100)
        res = 99;

    return res;
}

void Song::setEndBeat(float beat)
{
    endBeat_ = beat;
}

void Song::drawProgress(sf::RenderWindow& window, float beat, int section)
{
    if (section == -1)
        return;

    float y = 20;

    sf::CircleShape shape;
    sf::RectangleShape line, progress;

    float d1 = WIDOW_WIDTH * 0.1f, d2 = WIDOW_WIDTH * 0.9f;

    line.setFillColor(sf::Color(0xf7dd72ff));
    line.setPosition(d1, y - 3);
    line.setSize(sf::Vector2f(d2 - d1, 7));


    float fraction = beat / endBeat_;

    if (fraction > 1)
        fraction = 1;
    if (fraction < 0)
        fraction = 0;

    progress.setFillColor(sf::Color(0xf93943ff));
    progress.setPosition(d1, y - 5);
    progress.setSize(sf::Vector2f((d2 - d1) * fraction, 11));

    window.draw(line);
    window.draw(progress);

    shape.setRadius(15);

    for (int i = 0; i < checkpoints_.size(); i++) {
        if (beat >= checkpoints_[i].second)
            shape.setFillColor(sf::Color(0xf93943ff));
        else
            shape.setFillColor(sf::Color(0xf7dd72ff));

        shape.setPosition((d2 - d1) * checkpoints_[i].second / endBeat_ + d1 - 15, y - 15);

        window.draw(shape);
    }
    if (beat >= endBeat_)
        shape.setFillColor(sf::Color(0xf93943ff));
    else
        shape.setFillColor(sf::Color(0xf7dd72ff));
    shape.setPosition(d2 - 15, y - 15);
    window.draw(shape);
    
}

void Song::drawSection(sf::RenderWindow& window, float beat, int section)
{
    if (section == -1)
        return;

    float y = 330;

    sf::CircleShape shape;
    sf::RectangleShape line, progress;

    float d1 = WIDOW_WIDTH * 0.3f, d2 = WIDOW_WIDTH * 0.7f;

    line.setFillColor(sf::Color(0xf7dd72ff));
    line.setPosition(d1, y - 6);
    line.setSize(sf::Vector2f(d2 - d1, 13));


    float s1 = checkpoints_[section].second;
    float s2;
    if (section + 1 == checkpoints_.size()) {
        s2 = endBeat_;
    }
    else {
        s2 = checkpoints_[section + 1].second;
    }

    float fraction = (beat - s1) / (s2 - s1);

    if (fraction > 1)
        fraction = 1;
    if (fraction < 0)
        fraction = 0;

    progress.setFillColor(sf::Color(0xf93943ff));
    progress.setPosition(d1, y - 10);
    progress.setSize(sf::Vector2f((d2 - d1) * fraction, 21));

    window.draw(line);
    window.draw(progress);

    shape.setRadius(30);


    shape.setFillColor(sf::Color(0xf93943ff));
    shape.setPosition(d1 - 30, y - 30);

    window.draw(shape);
    

    shape.setFillColor(sf::Color(0xf7dd72ff));
    shape.setPosition(d2 - 30, y - 30);

    window.draw(shape);

}

void Song::resetCheckpoints() {
    checkpoints_.clear();
}

void Song::save(const std::string& filename, const std::vector<Mechanic *> &mechs, Arena &arena) {
    std::ofstream file(filename);

    file << "[Arena]" << std::endl;
    for (int i = 0; i < arena.getNbRects(); i++) {
        auto rect = arena.getRects(i);
        file << rect.left << "," << rect.top << "," << rect.width << "," << rect.height << std::endl;

    }


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
