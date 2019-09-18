#ifndef CHARACTER_H
#define CHARACTER_H

#include "image.h"

// concrete product
class Character : public Image
{
public:
    Character(QString path, Coordinate coordinate, unsigned int w, unsigned int h, QStringList list);
    ~Character();

    // for a character, changes between sprites, animating the character
    void animate();

private:
    QStringList sprites;
    unsigned int anim;
    int next;
};

#endif // CHARACTER_H
