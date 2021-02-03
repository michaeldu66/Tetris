#include "sprite.h"


Sprite::Sprite(string link_sprite):Surface(){
    this->set_surf(link_sprite);
    cout << "Sprite créé" << endl;
}