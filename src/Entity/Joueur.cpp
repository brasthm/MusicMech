//
// Created by cyril on 17/05/2022.
//

#include "Joueur.h"
#include "../main.h"
#include "../System/Utils.h"

#include <cmath>
#include <iostream>


Joueur::Joueur() {
    radius_ = BASE_PLAYER_RADIUS;
    shape_.setRadius(radius_);
    shape_.setOutlineThickness(3);
    shape_.setOutlineColor(sf::Color(sf::Color::White));
    shape_.setPointCount(100);
    shape_.setOrigin(radius_, radius_);
    pos_.x = ARENA_WIDTH/2.f; pos_.y = ARENA_HEIGHT/2.f; serv_pos_ = pos_;
    controlledByPlayer_ = false;
    speed_ = 700;
    active_ = false;
    name_ = "";
    baseSpeed_ = speed_;
}

void Joueur::update(sf::Time elapsed, float beat, bool hasFocus) {

    if(active_) {
        debuff_.update(elapsed, beat);
        sf::Vector2f vecDep(0,0);

        if(controlledByPlayer_ && hasFocus && debuff_.type() != DEBUFF_ROOT) {
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

        float length = std::sqrt(vecDep.x * vecDep.x + vecDep.y * vecDep.y);

        if(length != 0) {
            vecDep = vecDep/length;
            float diffX, diffY;
            if(!controlledByPlayer_) {
                diffX = vecDep.x;
                diffY = vecDep.y;
            }

            pos_ += vecDep*speed_*elapsed.asSeconds();

            if(!controlledByPlayer_) {
                float newDiffX, newDiffY;
                newDiffX = serv_pos_.x - pos_.x;
                newDiffY = serv_pos_.y - pos_.y;

                if(!Utils::sameSign(newDiffX, diffX))
                    pos_.x = serv_pos_.x;
                if(!Utils::sameSign(newDiffY, diffY))
                    pos_.y = serv_pos_.y;
            }
        }
    }

}

void Joueur::draw(sf::RenderWindow &window) {
    if(active_) {
        shape_.setPosition(serv_pos_);

        debuff_.draw(window, pos_);

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
    packet >> active_ >> x >> y;
    serv_pos_.x = x;
    serv_pos_.y = y;
}

void Joueur::reset() {
    debuff_.clense();
}
