#include "character.h"

Character::Character(QString path, Coordinate coordinate, unsigned int w, unsigned int h, QStringList list, QStringList jumpList) :
    Image(path, coordinate, w, h), sprites(list), jumpSprites(jumpList), anim(0)
{
    groundHeight = coordinate.getQtRenderingYCoordinate();
}

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

    // Jump logic
    i_coordinate.changeInYCoordinate(jumpSpeed);
    if (i_coordinate.getQtRenderingYCoordinate() < groundHeight) {
        jumpSpeed -= 10;
    } else {
        i_coordinate.setYCoordinateToZero(i_coordinate.getFrameHeight()-groundHeight);
        jumpSpeed = 0;
    }

    // Jump sprite logic
    if (jumpSpeed > 0) {
        this->setPath(jumpSprites[0]);
    } else if (jumpSpeed < 0) {
        this->setPath(jumpSprites[2]);
    } else if (jumpSpeed == 0 && i_coordinate.getQtRenderingYCoordinate() < groundHeight) {
        this->setPath(jumpSprites[1]);
    }
}

void Character::jump() {
    if (i_coordinate.getQtRenderingYCoordinate() == groundHeight) {
        jumpSpeed = 70;
        QSound::play(":/sounds/jump.wav");
    }
}

bool Character::intersects(Image *obstacle) {
    if (i_coordinate.getQtRenderingXCoordinate() < obstacle->getCoordinate().getQtRenderingXCoordinate() + obstacle->getWidth() &&
        obstacle->getCoordinate().getQtRenderingXCoordinate() < i_coordinate.getQtRenderingXCoordinate() + this->i_w &&
        i_coordinate.getQtRenderingYCoordinate() < obstacle->getCoordinate().getQtRenderingYCoordinate() + obstacle->getHeight() &&
        obstacle->getCoordinate().getQtRenderingYCoordinate() < i_coordinate.getQtRenderingYCoordinate() + this->i_h
    ) {
        return true;
    }
    return false;
}
