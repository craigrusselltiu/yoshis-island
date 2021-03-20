#ifndef CONFIG_H
#define CONFIG_H

#include <QDebug>
#include <QFile>
#include <QMap>
#include <QTextStream>

class Config {
public:
    Config(QString path);

    QMap<QString, QString> getMap();

    bool toBool(QString string);
    int getSize(QString string);

    // just a bunch of getters
    QString getBackground() {return background;}
    QString getForeground() {return foreground;}
    QString getCharacter() {return character;}
    QString getGoomba() {return goomba;}
    QString getKoopa() {return koopa;}
    bool isParallax() {return parallax;}
    bool isAnimated() {return animated;}
    unsigned int getCharSize() {return charSize;}
    unsigned int getResX() {return resX;}
    unsigned int getResY() {return resY;}
    unsigned int getStartPos() {return startPos;}
    unsigned int getStartVel() {return startVel;}
    unsigned int getBackgroundVel() {return backgroundVel;}

private:
    QString path;
    QMap<QString, QString> map;

    QString background, foreground, character, goomba, koopa;
    unsigned int resX, resY, startPos, startVel, backgroundVel, charSize;
    bool parallax, animated;
};

#endif // CONFIG_H
