#include "character.h"

Character::Character(QString path, Coordinate coordinate, unsigned int w, unsigned int h, QStringList list) :
    Image(path, coordinate, w, h), sprites(list), anim(0)
{}

Character::~Character() {}

// goes back and forth in the sprites list
void Character::animate() {

    // if the array doesn't just contain one image
    if (!(sprites.size() <= 1)) {

        // if the end of the list is reached, iterate backwards
        if (anim == sprites.size()-1) {
            next = -1;

        // if the start is reached, iterate forwards
        } else if (anim == 0) {
            next = 1;
        }

        // set next image render according to anim
        anim += next;
        this->setPath(sprites[anim]);
    }
}
