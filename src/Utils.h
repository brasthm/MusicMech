//
// Created by cyril on 13/05/2022.
//

#ifndef MUSICMECH_SERVER_UTILS_H
#define MUSICMECH_SERVER_UTILS_H

#include <string>
#include <SFML/Network.hpp>

namespace Utils {
    int hash(std::string key);
    bool sequence_greater_than(sf::Uint16 s1, sf::Uint16 s2);


}


#endif //MUSICMECH_SERVER_UTILS_H
