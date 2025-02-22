#ifndef DIALOG_H
#define DIALOG_H

#include "config.h"
#include "imagefactory.h"

#include <QKeyEvent>
#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public slots:
    void nextFrame();

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Dialog *ui;

    QTimer *timer;
    QLabel *pauseLabel, *titleLabel, *gameOver, *scoreLabel;
    QMediaPlaylist *playlist;
    QMediaPlayer *music;

    ImageFactory *factory;
    Image *background1, *background2, *parallax1, *parallax2, *clouds1, *clouds2, *character;
    QList<Image*> obstacles;
    Config config;
    bool paused, started, dead;
    int counter = 0, score = 0, random, spawnTime;
};

#endif // DIALOG_H
