#ifndef IMAGE_H
#define IMAGE_H

#include "coordinate.h"

#include <QPainter>
#include <QDebug>
#include <QString>
#include <QLabel>

// product
class Image {
public:

    // an image has a path, coordinates, and dimensions
    Image(QString path, Coordinate coordinate, unsigned int w, unsigned int h) :
        i_path(path), i_coordinate(coordinate), i_w(w), i_h(h) {}

    virtual ~Image() {}

    // render image by using drawPixmap function of painter
    virtual void renderImage(QPainter &painter) {
        QPixmap pixmap(i_path);

        // check if the file path is valid
        if (!pixmap.isNull()) {
            painter.drawPixmap(i_coordinate.getQtRenderingXCoordinate(), i_coordinate.getQtRenderingYCoordinate() - i_h,
                                 i_w, i_h, pixmap);
        } else {
            qDebug() << "ERROR: Could not find image with path " << i_path << "!";
        }
    }

    virtual Coordinate getCoordinate() {return i_coordinate;}
    virtual int getWidth() {return i_w;}
    virtual int getHeight() {return i_h;}

    virtual void setPath(QString set) {
        i_path = set;
    }

    virtual void setCoordinate(Coordinate set) {
        i_coordinate = set;
    }

    virtual void setSize(int width, int height) {
        i_w = width;
        i_h = height;
    }

    virtual void animate() = 0;

    // make character jump
    virtual void jump() {qDebug() << "bruh";}
    virtual bool offscreen() {return false;}
    virtual bool intersects(Image *obstacle) {return false;}

protected:
    QString i_path;
    Coordinate i_coordinate;
    unsigned int i_w, i_h;
};

#endif // IMAGE_H
