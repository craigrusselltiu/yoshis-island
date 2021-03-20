#ifndef CHARACTER_H
#define CHARACTER_H

#include "image.h"
#include <QSound>

// concrete product
class Character : public Image
{
public:
    Character(QString path, Coordinate coordinate, unsigned int w, unsigned int h, QStringList list, QStringList jumpList);
    ~Character();

    // for a character, changes between sprites, animating the character
    void animate();
    void jump();
    bool intersects(Image *obstacle);

private:
    QStringList sprites;
    QStringList jumpSprites;
    unsigned int anim;
    int next;
    int jumpSpeed = 0;
    int groundHeight;
};

#endif // CHARACTER_H
