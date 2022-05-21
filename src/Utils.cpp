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
