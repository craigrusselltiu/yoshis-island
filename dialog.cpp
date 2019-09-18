#include "dialog.h"
#include "ui_dialog.h"

#define CONFIG_PATH "://config.txt"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    config(CONFIG_PATH),
    paused(false), started(false)
{
    ui->setupUi(this);
    this->resize(config.getResX(), config.getResY());

    // initialise the factory and pass the config file to it
    ImageFactory factory(config);

    // initialise the images
    background1 = factory.newImage("background", 1);
    background2 = factory.newImage("background", 2);
    clouds1 = factory.newImage("background", 5);
    character = factory.newImage("character", 1);

    // if parallax is true, these must also be initialised
    if (config.isParallax()) {
        clouds2 = factory.newImage("background", 6);
        parallax1 = factory.newImage("background", 3);
        parallax2 = factory.newImage("background", 4);
    }

    // initialise the pause label
    pauseLabel = new QLabel(this);
    pauseLabel->setPixmap(QPixmap(":/images/paused.png"));
    pauseLabel->setGeometry((config.getResX()-400)/2, (config.getResY()-400)/2, 400, 400);
    pauseLabel->setScaledContents(true);
    pauseLabel->setVisible(false);

    // initialise the title label
    titleLabel = new QLabel(this);
    titleLabel->setPixmap(QPixmap(":/images/title.png"));
    titleLabel->setGeometry((config.getResX()-600)/2, (config.getResY()-300)/2, 600, 300);
    titleLabel->setScaledContents(true);

    // add music to QMediaPlaylist to loop infinitely, then play using QMediaPlayer
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/flowerGarden.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));

    // velocity increases as timer update decreases (default 100)
    timer->start(4000/config.getStartVel());
    timer->stop();
}

Dialog::~Dialog()
{
    // CLEANUP TIME
    delete ui;

    delete background1;
    delete background2;
    delete clouds1;
    delete clouds2;
    delete parallax1;
    delete parallax2;
    delete character;

    delete pauseLabel;
}

void Dialog::nextFrame() {
    update();
}

void Dialog::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    clouds1->renderImage(painter);

    // if parallax is true these would have been initialised
    if (config.isParallax()) {

        // render the images
        clouds2->renderImage(painter);
        parallax1->renderImage(painter);
        parallax2->renderImage(painter);

        // animate images, e.g. move background coordinates, sprite animations
        parallax1->animate();
        parallax2->animate();
        clouds1->animate();
        clouds2->animate();
    }

    background1->renderImage(painter);
    background2->renderImage(painter);
    character->renderImage(painter);

    background1->animate();
    background2->animate();
    character->animate();
}

// event for whenever a key is pressed
void Dialog::keyPressEvent(QKeyEvent *event) {

    // when p is pressed and the game has started
    if(event->key() == Qt::Key_P && started) {

        // if the game isn't paused
        if (!paused) {

            // stop the timer, show pause, pause the music
            timer->stop();
            pauseLabel->setVisible(true);
            music->pause();

        // otherwise the game must be paused
        } else {

            // restart the timer, hide pause, resume the music
            timer->start(4000/config.getStartVel());
            pauseLabel->setVisible(false);
            music->play();
        }

        QSound::play(":/sounds/pause.wav");
        paused = !paused;

    // when return is pressed and the game hasn't started
    } else if(event->key() == Qt::Key_Return && !started) {
        started = true;
        delete titleLabel;
        QSound::play(":/sounds/pause.wav");

        // start the game
        timer->start(4000/config.getStartVel());
    }
}
