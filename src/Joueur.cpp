//
// Created by cyril on 17/05/2022.
//

#include "Joueur.h"
#include "main.h"

#include <cmath>
#include <iostream>


Joueur::Joueur() {
    radius_ = BASE_PLAYER_RADIUS;
    shape_.setRadius(radius_);
    shape_.setOutlineThickness(3);
    shape_.setOutlineColor(sf::Color(sf::Color::White));
    shape_.setPointCount(100);
    shape_.setOrigin(radius_, radius_);
    pos_.x = 0; pos_.y = 0; serv_pos_ = pos_;
    controlledByPlayer_ = false;
    speed_ = 700;
    connected_ = false;
    name_ = "";
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

        if(controlledByPlayer_) {
            shape_.setFillColor(sf::Color(0x3B00EA80));
        }

        else
            shape_.setFillColor(sf::Color(0xFF007D80));

        window.draw(shape_);




        shape_.setPosition(pos_);
        if(controlledByPlayer_)
            shape_.setFillColor(sf::Color(0x3B00EAFF));
        else
            shape_.setFillColor(sf::Color(0xFF007DFF));
        window.draw(shape_);
    }
}


void Joueur::setDataFromServer(sf::Packet &packet)  {
    sf::Int32 x, y;
    packet >> connected_ >> x >> y;
    serv_pos_.x = x;
    serv_pos_.y = y;
}
