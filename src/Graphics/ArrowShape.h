//
// Created by cyril on 23/06/2022.
//

#ifndef MUSICMECH_CLIENT_ARROWSHAPE_H
#define MUSICMECH_CLIENT_ARROWSHAPE_H

#include <SFML/Graphics.hpp>
#include "ShiftColor.h"

class ArrowShape {
private:
    ShiftColor color_;
    sf::RectangleShape up_, down_;
    sf::Vector2f position_;
    float rotation_;
    float scale_;

public:
    ArrowShape();
    void draw(sf::RenderTarget &window);
    void update(const sf::Time &elapsed);
    void setPosition(sf::Vector2f pos);
    void setScale(float scale);
    void setRotation(float rotation);
    void addColor(const std::string &key, sf::Uint32 color);
    void setCurrent(const std::string &key);
    void setColorSpeed(const std::array<float, 4> &speed);
    float getWidth() const;

};


#endif //MUSICMECH_CLIENT_ARROWSHAPE_H
