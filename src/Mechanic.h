//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_MECHANIC_H
#define MUSICMECH_CLIENT_MECHANIC_H

#include <SFML/Graphics.hpp>



class Mechanic {
protected:
    int beat_;
    std::string sound_;
    bool played_;

    void setSoundName(const std::string& name);
    void playSound();
public:
    Mechanic();
    ~Mechanic() = default;
    virtual void update(int currentBeat, float currentPart) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

};


#endif //MUSICMECH_CLIENT_MECHANIC_H
