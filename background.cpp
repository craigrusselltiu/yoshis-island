#include "background.h"

Background::Background(QString path, Coordinate coordinate, unsigned int w, unsigned int h, unsigned int speed) :
    Image(path, coordinate, w, h), i_default(coordinate.getQtRenderingXCoordinate()), i_speed(speed)
{}

Background::~Background() {}

// when setting the coordinate, also changes the default coordinate position
void Background::setCoordinate(Coordinate set) {
    i_coordinate = set;
    i_default = set.getQtRenderingXCoordinate();
}

void Background::setSpeed(unsigned int speed) {
    i_speed = speed;
}

// moves the background from right to left
void Background::animate() {
    i_coordinate.changeInXCoordinate(-i_speed);

    // if it passes its size, then reset the X coordinate to default
    if (i_coordinate.getQtRenderingXCoordinate() + (signed)i_w <= i_default) {
        i_coordinate.changeInXCoordinate(i_w);
    }
}
