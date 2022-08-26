//
// Created by cyril on 30/05/2022.
//

#ifndef MUSICMECH_CLIENT_PLAYERINDICATOR_H
#define MUSICMECH_CLIENT_PLAYERINDICATOR_H

#include <SFML/Graphics.hpp>


class PlayerIndicator {
    std::vector<sf::RectangleShape> lights_;
    sf::Vector2f position_, offset_;
    sf::Color outlineColor_, fillColor_;
    int nbTot_;
    float c_, step_;

public:
    PlayerIndicator(sf::Vector2f pos, sf::Vector2f offset, int nbTot,
                    float c, float g);
    void updatePosition(sf::Vector2f position);
    void updateAlpha(float alpha);
    void draw(sf::RenderTarget &window);
    void updateLight(int nb);

    void setFillColor(sf::Uint32 fillColor);
    void setOutlineColor(sf::Uint32 outlineColor);
};


#endif //MUSICMECH_CLIENT_PLAYERINDICATOR_H
