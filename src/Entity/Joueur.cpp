//
// Created by cyril on 17/05/2022.
//

#include "Joueur.h"
#include "../main.h"
#include "../System/Utils.h"
#include "../System/RessourceLoader.h"

#include <array>
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
    color_ = 0x888888FF;
    baseSpeed_ = speed_;

    plateOpacity_ = 255;
    nameText_.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
    nameText_.setCharacterSize(28);
    drawPlate_ = false;    
}

bool Joueur::update(sf::Time elapsed, Arena* arena, float beat, bool hasFocus) {
    shape_.setOrigin(radius_, radius_);
    shape_.setRadius(radius_);
    if(active_) {
        for (int i = 0; i < debuffs_.size(); i++) {
            bool val = debuffs_[i].update(elapsed, beat);
            if (val) return true;
        }

        sf::Vector2f vecDep(0,0);

        for (int i = 0; i < debuffs_.size(); i++) {
            if (debuffs_[i].type() == DEBUFF_ROOT)
                return false;
        }

        if (IS_SERVER)
            return false;

        if (drawPlate_) {
            if (plateLimit_.asSeconds() != 0) {
                if (plateTimer_.getElapsedTime() > plateLimit_) {
                    plateOpacity_ -= 255 * elapsed.asSeconds();
                    if (plateOpacity_ < 0) {
                        plateOpacity_ = 0;
                        drawPlate_ = false;
                    }
                }
            }
        }

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

            float deadzone = JOYSTICK_DEADZONE/100;
            float maxzone = JOYSTICK_MAXZONE/100;
            const std::array<sf::Joystick::Axis, 2> stickX = { sf::Joystick::X, sf::Joystick::U };  // left stick, right stick
            const std::array<sf::Joystick::Axis, 2> stickY = { sf::Joystick::Y, sf::Joystick::V };
            //std::cout << "---" << std::endl;
            for (int gamepad = 0; gamepad < 8; gamepad++)
            {
                if (!sf::Joystick::isConnected(gamepad))
                    continue;
                //std::cout << "gamepad " << gamepad << " - x: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::X) << ", y: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::Y) << ", povx: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::PovX) << ", povy: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::PovY) << ", z: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::Z) << ", r: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::R) << ", u: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::U) << ", v: " << sf::Joystick::getAxisPosition(gamepad, sf::Joystick::V) << std::endl;

                for (size_t stick = 0; stick < stickX.size(); stick++)
                {
                    if (!sf::Joystick::hasAxis(gamepad, stickX[stick]) || !sf::Joystick::hasAxis(gamepad, stickY[stick]))
                        continue;
                    sf::Vector2f stickPos = sf::Vector2f(sf::Joystick::getAxisPosition(gamepad, stickX[stick]) / 100,
                                                         sf::Joystick::getAxisPosition(gamepad, stickY[stick]) / 100);
                    vecDep += Utils::remapLength(stickPos, deadzone, maxzone, 0, 1, true);
                    //auto p = Utils::remapLength(stickPos, deadzone, maxzone, 0, 1, true);
                    //std::cout << "stick " << stick << ": " << p.x << ", " << p.y << std::endl;
                }
            }
        }
        else if (!controlledByPlayer_){
            vecDep = serv_pos_ - pos_;
        }

        float length = std::sqrt(vecDep.x * vecDep.x + vecDep.y * vecDep.y);

        if(length != 0) {
            if (length > 1)
                vecDep = vecDep/length;

            float diffX, diffY;
            if(!controlledByPlayer_) {
                diffX = vecDep.x;
                diffY = vecDep.y;
            }

            pos_ += vecDep*speed_*elapsed.asSeconds();

            if (!arena->contains(pos_)) {
                pos_ = arena->getClosest(pos_);
            }

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

    return false;

}

void Joueur::draw(sf::RenderTarget &window, bool serverPos) {
    if(active_) {
        if (serverPos) {
            shape_.setPosition(serv_pos_);
            shape_.setFillColor(sf::Color(color_ - 0x88));
            window.draw(shape_);
        }

        int index = -1;
        for (int i = 0; i < debuffs_.size(); i++) {
            if (debuffs_[i].isNotif()) {
                int val = debuffs_[i].getNotif();
                if(index < val) index = val;
            }
        }

        

        for (int i = 0; i < debuffs_.size(); i++) {
            debuffs_[i].draw(window, pos_);
            if (debuffs_[i].isNotif()) {
                if(debuffs_[i].getNotif() == -1) index++;
                debuffs_[i].setNotif(index);
                debuffs_[i].notification(window, pos_);
            }
        }

        shape_.setPosition(pos_);
        shape_.setFillColor(sf::Color(color_));
        window.draw(shape_);

        if (drawPlate_) {
            auto size = namePlate_.getGlobalBounds();
            namePlate_.setPosition(pos_.x - size.width / 2, pos_.y - size.height - 30);
            nameText_.setPosition(pos_.x - size.width / 2 + 5, pos_.y - size.height - 30);

            sf::Color c(color_), w(sf::Color::Black);

            c.a = plateOpacity_;
            w.a = plateOpacity_;

            namePlate_.setFillColor(c);
            nameText_.setFillColor(w);

            window.draw(namePlate_);
            window.draw(nameText_);
        }
    }
}


void Joueur::setDataFromServer(sf::Packet &packet)  {
    sf::Int32 x, y;
    bool active;
    packet >> active >> x >> y;

    if (!packet) {
        std::cout << "TCP_SOCKET : Invalid packet (setDataFromServer)." << std::endl;
        return;
    }

    active_ = active;
    serv_pos_.x = x;
    serv_pos_.y = y;
}

void Joueur::reset() {
    debuffs_.clear();
}

void Joueur::setName(std::string name)
{
    name_ = name;
}

void Joueur::showPlate(bool permanant)
{
    drawPlate_ = true;
    plateOpacity_ = 255;
    plateLimit_ = sf::seconds(permanant ? 0:3);
    plateTimer_.restart();
}

void Joueur::hidePlate()
{
    drawPlate_ = false;
}

void Joueur::computePlate()
{
    namePlate_.setFillColor(sf::Color(color_));
    nameText_.setString(name_);
    auto size = nameText_.getGlobalBounds();
    namePlate_.setSize(sf::Vector2f(size.width + 15, size.height + 15));
}



std::string Joueur::getName()
{
    return name_;
}
