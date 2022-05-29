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
    bool draw_;
    float active_;


    sf::Vector3f colorCurrent_, colorTarget_;
    float alpha_;
    sf::Color colorGood_, colorFailed_;
    sf::Vector3f speedColor_;

    void setSoundName(const std::string& name);
    void playSound();
public:
    Mechanic();
    ~Mechanic() = default;
    void update(const sf::Time &elapsed, float currentBeat, std::vector<Joueur> &joueurs);
    void draw(sf::RenderWindow &window);


    virtual std::string toString()=0;
    virtual inline void onDraw(sf::RenderWindow &window) {};
    virtual inline void onCheck(std::vector<Joueur> &joueurs) {};
    virtual inline void onApproach(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {};
    virtual inline void onPassed(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {};
    virtual inline void onFailed(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {};
    virtual inline void onFade(float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {};

    void setColorTarget(const sf::Color &color);
    void updateColor(const sf::Time &elapsed);


};




#endif //MUSICMECH_CLIENT_MECHANIC_H
