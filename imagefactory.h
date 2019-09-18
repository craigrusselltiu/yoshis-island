#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H

#include "character.h"
#include "background.h"
#include "config.h"

// concrete factory, creates different images depending on the input
// the factory method is used to reduce code repetition in creating image objects with custom functions and properties
class ImageFactory {
public:

    ImageFactory(Config input) : config(input) {

        // initialise map when factory is created
        i_map = config.getMap();
    }

    // creates a list of sprites for animation from parameter key
    //
    // e.g. if input is "sprite", then finds "sprite1", "sprite2", etc. in config file
    QStringList createAnimation(QString key) {

        QStringList list;

        if (config.isAnimated()) {
            int counter = 1;
            QString temp = key + QString::number(counter);

            while(i_map.contains(temp)) {
                list << i_map[temp];
                counter++;
                temp = key + QString::number(counter);
            }
        }

        return list;
    }

    // returns concrete product type depending on input "type"
    // returns either a premade or object or a default one depending on input "select"
    //
    // to return an editable, generic product, use select = 0
    // e.g. factory.newImage("character", 0);
    Image* newImage(QString type, int select) {

        // reassign some config values for ease of use
        int resX = config.getResX();
        int resY = config.getResY();
        int velocity = config.getBackgroundVel();
        int size = config.getCharSize();

        // ratio from the recommended 600 frame height
        int ratio = resY/600;

        // create a character
        if (type == "character") {

            // premade characters, e.g. select = 1 returns main character
            if (select == 1) {
                QStringList list = createAnimation("sprite");

                // return a character of size, size*ratio
                return new Character(config.getCharacter(), Coordinate(config.getStartPos(), resY/6, resY), size*ratio, size*ratio, list);

            // return default, editable, generic character
            } else {
                QStringList list;
                return new Character(config.getCharacter(), Coordinate(0, 0, resY), size*ratio, size*ratio, list);
            }

        // create a background image or object
        } else if (type == "background") {

            // premade backgrounds, e.g. select = 1 returns foreground, select = 5 returns clouds
            if (select == 1) {
                return new Background(config.getForeground(), Coordinate(0, 0, resY), resX, resY, velocity);
            } else if (select == 2) {
                return new Background(config.getForeground(), Coordinate(resX, 0, resY), resX, resY, velocity);
            } else if (select == 3) {
                return new Background(config.getForeground(), Coordinate(0, 50, resY), resX, resY, velocity/2);
            } else if (select == 4) {
                return new Background(config.getForeground(), Coordinate(resX, 50, resY), resX, resY, velocity/2);
            } else if (select == 5) {
                return new Background(config.getBackground(), Coordinate(0, 100, resY), resX, resY, velocity/3);
            } else if (select == 6) {
                return new Background(config.getBackground(), Coordinate(resX, 100, resY), resX, resY, velocity/3);

            // return default, editable, generic background image
            } else {
                return new Background(config.getForeground(), Coordinate(0, 0, resY), resX, resY, velocity);
            }

        // otherwise return a null pointer
        } else {
            return nullptr;
        }
    }

private:
    Config config;
    QMap<QString, QString> i_map;
};

#endif // IMAGEFACTORY_H
