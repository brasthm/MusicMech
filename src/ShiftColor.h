//
// Created by cyril on 17/06/2022.
//

#ifndef MUSICMECH_CLIENT_SHIFTCOLOR_H
#define MUSICMECH_CLIENT_SHIFTCOLOR_H

#include <SFML/Graphics.hpp>
#include <array>
#include <map>


class ShiftColor {
private:
    std::map<std::string, std::array<float, 4>> colorTargets_;
    std::string currentTarget_, prevTarget_;
    std::array<float, 4> colorCurrent_;
    std::array<float,4> speedColor_;

public:
    ShiftColor() = default;
    void updateColor(const sf::Time &elapsed);
    void setSpeed(int index, float val);
    void setCurrentColor(int index, float val);
    void setSpeed(const std::array<float,4> &speed);
    void addTarget(const std::string& key, sf::Uint32 color);
    void setCurrentTarget(const std::string& target);
    sf::Color getCurrentColor();
    void initCurrent(const std::string &key);

};


#endif //MUSICMECH_CLIENT_SHIFTCOLOR_H
