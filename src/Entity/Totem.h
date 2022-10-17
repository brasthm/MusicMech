//
// Created by cyril on 26/06/2022.
//

#ifndef MUSICMECH_CLIENT_TOTEM_H
#define MUSICMECH_CLIENT_TOTEM_H

#include "Entity.h"

class Totem : public Entity {
private:
    bool draw_;
public:
    Totem();
    void update(sf::Time elapsed, Arena* arena, float beat);
    void draw(sf::RenderTarget &window);

};


#endif //MUSICMECH_CLIENT_TOTEM_H
