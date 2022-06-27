//
// Created by cyril on 26/06/2022.
//

#ifndef MUSICMECH_CLIENT_TOTEM_H
#define MUSICMECH_CLIENT_TOTEM_H

#include "Entity.h"

class Totem : public Entity {
private:
    bool draw_, active_;
public:
    Totem();
    void update(sf::Time elapsed, bool hasFocus) override;
    void draw(sf::RenderWindow &window) override;
    void setActive(bool val);
};


#endif //MUSICMECH_CLIENT_TOTEM_H
