//
// Created by cyril on 30/05/2022.
//

#ifndef MUSICMECH_CLIENT_PLAYERINDICATOR_H
#define MUSICMECH_CLIENT_PLAYERINDICATOR_H

#include <SFML/Graphics.hpp>


class PlayerIndicator {
    std::vector<sf::RectangleShape> lights_;
    sf::Vector2f position_;
    sf::Color outlineColor_, fillColor_;
    int nbTot_;
    float c_, step_;

public:
    PlayerIndicator(sf::Vector2f pos, int nbTot,
                    sf::Uint32 outlineColor, sf::Uint32 fillColor,
                    float c, float g);
    void updatePosition();
    void updateAlpha(float alpha);
    void draw(sf::RenderWindow &window);
    void updateLight(int nb);
};


#endif //MUSICMECH_CLIENT_PLAYERINDICATOR_H
