//
// Created by cyril on 13/05/2022.
//

#include "../src/Utils.h"

#include <cmath>

int Utils::hash(std::string key) {
    const int PRIME_CONST = 2;

    int hashCode = 0;
    for (int i = 0; i < key.length(); i++) {
        hashCode += key[i] * pow(PRIME_CONST, i);
        hashCode = hashCode % 16777216;
    }

    return hashCode;
}

bool Utils::sequence_greater_than(sf::Uint16 s1, sf::Uint16 s2) {
    return ( ( s1 > s2 ) && ( s1 - s2 <= 32768 ) ) ||
           ( ( s1 < s2 ) && ( s2 - s1  > 32768 ) );

}

std::vector<std::string> Utils::split(std::string s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}

double Utils::distance(sf::Vector2f a, sf::Vector2f b) {
    auto diff = a - b;
    return sqrt(diff.x * diff.x + diff.y * diff.y);
}

sf::Vector3f Utils::RGBtoHSV(const sf::Color &color) {
    float R = color.r / 255.f;
    float G = color.g / 255.f;
    float B = color.b / 255.f;

    float M = std::max({ R, G, B });
    float m = std::min({ R, G, B });
    float C = M - m; // Chroma

    float H = 0.f; // Hue
    float S = 0.f; // Saturation
    float V = 0.f; // Value

    if (C != 0.f)
    {
        if (M == R)
            H = std::fmod(((G - B) / C), 6.f);
        else if (M == G)
            H = ((B - R) / C) + 2;
        else if (M == B)
            H = ((R - G) / C) + 4;

        H *= 60;
    }

    if (H < 0.f)
        H += 360;

    V = M;

    if (V != 0.f)
        S = C / V;

    return { H, S, V };
}

sf::Color Utils::HSVtoRGB(sf::Vector3f color) {

    float H, S, V;
    H = color.x;
    S = color.y;
    V = color.z;

    float C = S * V; // Chroma
    float HPrime = std::fmod(H / 60, 6.f); // H'
    float X = C * (1 - std::fabs(std::fmod(HPrime, 2.f) - 1));
    float M = V - C;

    float R = 0.f;
    float G = 0.f;
    float B = 0.f;

    switch (static_cast<int>(HPrime))
    {
        case 0: R = C; G = X;        break; // [0, 1)
        case 1: R = X; G = C;        break; // [1, 2)
        case 2:        G = C; B = X; break; // [2, 3)
        case 3:        G = X; B = C; break; // [3, 4)
        case 4: R = X;        B = C; break; // [4, 5)
        case 5: R = C;        B = X; break; // [5, 6)
    }

    R += M;
    G += M;
    B += M;

    sf::Color color2;
    color2.r = static_cast<sf::Uint8>(std::round(R * 255));
    color2.g = static_cast<sf::Uint8>(std::round(G * 255));
    color2.b = static_cast<sf::Uint8>(std::round(B * 255));

    return color2;
}
