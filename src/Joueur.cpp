//
// Created by cyril on 17/05/2022.
//

#include "Joueur.h"

#include <cmath>
#include <iostream>


Joueur::Joueur() {
    shape_.setRadius(20);
    shape_.setFillColor(sf::Color::Green);
    pos_.x = 0; pos_.y = 0; serv_pos_ = pos_;
    controlledByPlayer_ = false;
    speed_ = 700;
    connected_ = false;
}

void Joueur::update(sf::Time elapsed, bool hasFocus) {

    if(connected_) {
        sf::Vector2f vecDep(0,0);

        if(controlledByPlayer_ && hasFocus) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                vecDep.y = -1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                vecDep.y = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                vecDep.x = -1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                vecDep.x = 1;
            }
        }
        else if (!controlledByPlayer_){
            vecDep = serv_pos_ - pos_;
        }

        float length = sqrt(vecDep.x * vecDep.x + vecDep.y * vecDep.y);

        if(length != 0) {
            vecDep = vecDep/length;
            pos_ += vecDep*speed_*elapsed.asSeconds();
        }
    }

}

void Joueur::draw(sf::RenderWindow &window) {
    if(connected_) {
        shape_.setPosition(serv_pos_);

        if(controlledByPlayer_)
            shape_.setFillColor(sf::Color(0, 255, 0, 128));
        else
            shape_.setFillColor(sf::Color(255, 0, 0, 128));

        window.draw(shape_);




        shape_.setPosition(pos_);
        if(controlledByPlayer_)
            shape_.setFillColor(sf::Color::Green);
        else
            shape_.setFillColor(sf::Color::Red);
        window.draw(shape_);
    }
}


void Joueur::setDataFromServer(sf::Packet &packet)  {
    sf::Int32 x, y;
    packet >> connected_ >> x >> y;
    serv_pos_.x = x;
    serv_pos_.y = y;
}
