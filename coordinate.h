#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>

class Coordinate {
public:
    Coordinate(unsigned
        int xCoordinate,
        unsigned int yCoordinate,
        unsigned int frameHeight);

    int getQtRenderingXCoordinate();
    int getQtRenderingYCoordinate();

    void changeInXCoordinate(int change);
    void changeInYCoordinate(int change);

    void setYCoordinateToZero(int offset);

    unsigned int getFrameHeight();

private:
    unsigned int m_xCoordinate;
    unsigned int m_yCoordinate;
    unsigned int m_frameHeight;
};

#endif // COORDINATE_H
