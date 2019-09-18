#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "image.h"

// concrete product
class Background : public Image
{
public:
    Background(QString path, Coordinate coordinate, unsigned int w, unsigned int h, unsigned int speed);
    ~Background();

    void setCoordinate(Coordinate set);
    void setSpeed(unsigned int speed);

    // for a background, moves the image to the left, and resets it once it passes its own size
    void animate();

private:
    int i_default, i_speed;
};

#endif // BACKGROUND_H
