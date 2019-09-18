#include "coordinate.h"

Coordinate::Coordinate(unsigned int xCoordinate, unsigned int yCoordinate, unsigned int frameHeight) :
    m_xCoordinate(xCoordinate), m_yCoordinate(yCoordinate), m_frameHeight(frameHeight)
{}

int Coordinate::getQtRenderingXCoordinate() {
    return m_xCoordinate;
}

// the Y coordinates are inverted to mimic normal graph representation
int Coordinate::getQtRenderingYCoordinate() {
    return m_frameHeight - m_yCoordinate;
}

void Coordinate::changeInXCoordinate(int change) {
    m_xCoordinate += change;
}

void Coordinate::changeInYCoordinate(int change) {
    m_yCoordinate += change;
}

void Coordinate::setYCoordinateToZero(int offset) {
    m_yCoordinate = 0;
    m_yCoordinate += offset;
}

unsigned int Coordinate::getFrameHeight() {
    return m_frameHeight;
}
