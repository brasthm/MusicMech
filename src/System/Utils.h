//
// Created by cyril on 13/05/2022.
//

#ifndef MUSICMECH_SERVER_UTILS_H
#define MUSICMECH_SERVER_UTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

namespace Utils {
    int hash(std::string key);
    bool sequence_greater_than(sf::Uint16 s1, sf::Uint16 s2);
    std::vector<std::string> split(std::string s, char delim);
    float distance(sf::Vector2f a, sf::Vector2f b);
    float distance(const std::array<float, 4> &a, const std::array<float, 4> &b);
    std::array<float, 4> RGBtoHSV(const sf::Color& color);
    sf::Color HSVtoRGB(const std::array<float, 4> &color);
    std::string paddLeft(std::string s, int nbPad, char padChar = ' ');
    std::array<float, 4> diff(const std::array<float, 4> &a, const std::array<float, 4> &b);
    bool sameSign(float a, float b);

    inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
    {
        s.erase(0, s.find_first_not_of(t));
        return s;
    }
    inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
    {
        s.erase(s.find_last_not_of(t) + 1);
        return s;
    }
    inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
    {
        return ltrim(rtrim(s, t), t);
    }
}


#endif //MUSICMECH_SERVER_UTILS_H
