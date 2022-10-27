//
// Created by cyril on 03/07/2022.
//

#ifndef MUSICMECH_CLIENT_DEBUFF_H
#define MUSICMECH_CLIENT_DEBUFF_H


#include <SFML/Graphics.hpp>

#include "../Graphics/ShiftColor.h"
#include "RessourceLoader.h"


enum DebuffType {
    DEBUFF_NONE, DEBUFF_ROOT, DEBUFF_CRITICAL, DEBUFF_SUDDENDEATH, DEBUFF_MASK1, DEBUFF_MASK2
};

class Debuff {
private:
    std::string name_, desc_, iconPath_, drawName_, drawPath_, drawDesc_;
    float end_;
    bool drawIcon_, startDraw_, endDraw_, oldDrawIcon_;
    DebuffType type_;
    sf::CircleShape shape_;
    ShiftColor color_;
    sf::Time timer_;
    int notif_;

    void setParams();

public:
    Debuff();
    bool update(sf::Time elapsed, float beat);
    void draw(sf::RenderTarget &window, sf::Vector2f position);
    void notification(sf::RenderTarget& window, sf::Vector2f position);
    void apply(DebuffType, float end);
    void clense();
    bool isNotif();
    void setNotif(int val);
    int getNotif();
    std::string getIcon();
    float getEnd();
    DebuffType type();
    bool getDrawIcon();
    std::string getName();
    std::string getDesc();
};


#endif //MUSICMECH_CLIENT_DEBUFF_H
