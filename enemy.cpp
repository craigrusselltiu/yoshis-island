#include "enemy.h"

Enemy::Enemy(QString path, Coordinate coordinate, unsigned int w, unsigned int h, unsigned int speed, QStringList list) :
    Image(path, coordinate, w, h), sprites(list), speed(speed), anim(0)
{}

Enemy::~Enemy() {}

void Enemy::animate() {
    i_coordinate.changeInXCoordinate(-speed);

    // if the array doesn't just contain one image
    if (!(sprites.size() <= 1)) {

        // if the end of the list is reached
        if (anim == sprites.size()*2-1) {
            anim = 0;
        }

        // set next image render according to anim
        anim++;
        this->setPath(sprites[anim/2]);
    }
}

bool Enemy::offscreen() {
    if (i_coordinate.getQtRenderingXCoordinate() < -75) {
        return true;
    }
    return false;
}
