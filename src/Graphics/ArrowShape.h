//
// Created by cyril on 23/06/2022.
//

#ifndef MUSICMECH_CLIENT_ARROWSHAPE_H
#define MUSICMECH_CLIENT_ARROWSHAPE_H

#include <SFML/Graphics.hpp>
#include "ShiftColor.h"

class ArrowShape {
private:
    sf::Color color_, outline_;
    sf::RectangleShape up_, down_;
    sf::RectangleShape outlineUp_, outlineDown_;
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
    void setColor(sf::Uint32 color);
    void setAlpha(float alpha);
    float getWidth() const;

};


#endif //MUSICMECH_CLIENT_ARROWSHAPE_H
