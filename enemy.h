#ifndef ENEMY_H
#define ENEMY_H

#include "image.h"

class Enemy : public Image
{
public:
    Enemy(QString path, Coordinate coordinate, unsigned int w, unsigned int h, unsigned int speed, QStringList list);
    ~Enemy();
    void animate();
    bool offscreen();

private:
    QStringList sprites;
    int speed, anim;
};

#endif // ENEMY_H
