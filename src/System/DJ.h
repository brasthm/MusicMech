//
// Created by cyril on 22/05/2022.
//

#ifndef MUSICMECH_CLIENT_DJ_H
#define MUSICMECH_CLIENT_DJ_H

#include <SFML/Audio.hpp>


#include "../main.h"
#include "RessourceLoader.h"



class DJ {
private:
    std::vector<sf::Sound> sounds_;
    std::vector<sf::Music> musics_;

    sf::Clock clock_;
    sf::Time elapsed_;

    int currentSound_;
    int currentMusic_;

    inline static DJ *djInstance_;

    DJ() : sounds_(NB_MAX_SOUND), musics_(NB_MAX_MUSIC){
        currentSound_ = 0;
        currentMusic_ = 0;
        clock_.restart();
        elapsed_ = sf::seconds(1);

        for (int i = 0; i < NB_MAX_SOUND; i++) {
            sounds_[i].setVolume(10);
        }
    };

    inline ~DJ() {
        delete djInstance_;
    };

    inline static DJ *getDjInstance() {
        if (!djInstance_)
            djInstance_ = new DJ();
        return djInstance_;
    };



    int playSound_(const std::string& path) {
        elapsed_ += clock_.getElapsedTime();
        clock_.restart();
        if(elapsed_ > sf::milliseconds(30)) {
            elapsed_ = sf::seconds(0);

            int returnval = currentSound_;

            sounds_[currentSound_].setBuffer(RessourceLoader::getSoundBuffer(path));
            sounds_[currentSound_].play();

            currentSound_++;
            currentSound_  = currentSound_ % NB_MAX_SOUND;

            return returnval;
        }


        return 0;
    };

    int playMusic_(const std::string& path) {
        int returnval = currentSound_;

        musics_[currentSound_].openFromFile(RessourceLoader::getPath(path));
        musics_[currentSound_].play();

        currentMusic_++;
        currentMusic_  = currentMusic_ % NB_MAX_MUSIC;

        return returnval;
    };


public:
    inline static int playSound(const std::string& path) {
        return getDjInstance()->playSound_(path);
    };

    inline static int playMusic(const std::string& path) {
        return  getDjInstance()->playMusic_(path);
    };


    DJ(const DJ&) = delete;
    DJ& operator= (const DJ) = delete;

};


#endif //MUSICMECH_CLIENT_DJ_H
