#include "config.h"

Config::Config(QString path) : path(path) {

    // create a map of the config file when constructor is called
    QMap<QString, QString> map;
    QFile file(path);

    // find a file and attempt to read from it
    if (file.open(QIODevice::ReadOnly)) {

        QTextStream in(&file);
        while (!in.atEnd()) {

            // reads line and splits from "="
            QString line = in.readLine();
            QStringList pieces = line.split("=");
            QString key = pieces.value(0);
            QString value = pieces.value(1);

            // assign left as key, and right as value
            map[key] = value;
        }
        file.close();

    // otherwise, print an error message
    } else {
        qDebug() << "ERROR: Could not find file with path " << path << "!";
    }

    this->map = map;

    // initialise config values into the class for ease of use
    resX = map["resX"].toInt();
    resY = map["resY"].toInt();
    backgroundVel = map["backgroundVel"].toInt();
    startPos = map["startPos"].toInt();
    startVel = map["startVel"].toInt();

    charSize = getSize(map["charSize"]);
    character = map["character"];
    foreground = map["foreground"];
    background = map["background"];

    parallax = toBool(map["parallax"]);
    animated = toBool(map["animated"]);
}

// takes a QString and output it as a bool
bool Config::toBool(QString string) {
    if (string == "true") {
        return true;
    } else if (string == "false") {
        return false;
    } else {
        qDebug() << "ERROR: Invalid bool value! Default initialised. (true)";
        return true;
    }
}

// return an int value depending on the config character size
int Config::getSize(QString string) {
    if (string == "tiny") {
        return 64;
    } else if (string == "normal") {
        return 128;
    } else if (string == "large") {
        return 256;
    } else if (string == "giant") {
        return 512;
    } else {
        qDebug() << "ERROR: Invalid character size! Default initialised. (128)";
        return 128;
    }
}

// returns the config map
QMap<QString, QString> Config::getMap() {
    return map;
}
