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
    int drawPriority_;

    void setSoundName(const std::string& name);
    void playSound();
public:
    Mechanic();
    ~Mechanic() = default;
    void update(const sf::Time &elapsed, float currentBeat, std::vector<Joueur> &joueurs);
    void draw(const sf::Time &elapsed, sf::RenderWindow &window);

    int getDrawPriority() const;
    bool operator< (const Mechanic& mech) const;
    float getBeat() const;


    virtual std::string toString() { return ""; };
    virtual inline void onDraw(const sf::Time &elapsed, sf::RenderWindow &window) {};
    virtual inline void onCheck(const sf::Time &elapsed, std::vector<Joueur> &joueurs) {};
    virtual inline void onApproach(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {};
    virtual inline void onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {};
    virtual inline void onFailed(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {};
    virtual inline void onFade(const sf::Time &elapsed, float currentBeat, float currentPart, std::vector<Joueur> &joueurs) {};


};




#endif //MUSICMECH_CLIENT_MECHANIC_H
