#include "sprite.h"
#include "surface.h"


Sprite::Sprite(const char* link_sprite):Surface(){
    this->set_surf(link_sprite);
    cout << "Sprite créé" << endl;
}
