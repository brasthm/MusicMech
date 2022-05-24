//
// Created by cyril on 21/05/2022.
//

#ifndef MUSICMECH_CLIENT_MECHANIC_H
#define MUSICMECH_CLIENT_MECHANIC_H

#include <SFML/Graphics.hpp>

#include "Joueur.h"


class Mechanic {
protected:
    float beat_;
    std::string sound_;
    bool played_, checked_;
    bool passed_;


    sf::Vector3f colorCurrent_, colorTarget_;
    sf::Color colorGood_, colorFailed_;
    sf::Vector3f speedColor_;

    void setSoundName(const std::string& name);
    void playSound();
public:
    Mechanic();
    ~Mechanic() = default;
    virtual void update(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void check(std::vector<Joueur> &joueurs) = 0;
    virtual std::string toString()=0;

    void setColorTarget(const sf::Color &color);
    void updateColor(const sf::Time &elapsed);


};




#endif //MUSICMECH_CLIENT_MECHANIC_H
