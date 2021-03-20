#include "dialog.h"
#include "ui_dialog.h"

#define CONFIG_PATH "://config.txt"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    config(CONFIG_PATH),
    paused(false), started(false), dead(false)
{
    ui->setupUi(this);
    this->resize(config.getResX(), config.getResY());

    // initialise the factory and pass the config file to it
    factory = new ImageFactory(config);

    // initialise the images
    background1 = factory->newImage("background", 1);
    background2 = factory->newImage("background", 2);
    clouds1 = factory->newImage("background", 5);
    character = factory->newImage("character", 1);

    // if parallax is true, these must also be initialised
    if (config.isParallax()) {
        clouds2 = factory->newImage("background", 6);
        parallax1 = factory->newImage("background", 3);
        parallax2 = factory->newImage("background", 4);
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
    titleLabel->setGeometry((config.getResX()-600)/2, (config.getResY()-400)/2, 600, 400);
    titleLabel->setScaledContents(true);

    // initialise the game over label
    gameOver = new QLabel(this);
    gameOver->setPixmap(QPixmap(":/images/gameover.png"));
    gameOver->setGeometry((config.getResX()-600)/2, (config.getResY()-400)/2, 600, 400);
    gameOver->setScaledContents(true);
    gameOver->setVisible(false);

    // initialise score label
    scoreLabel = new QLabel(this);
    scoreLabel->setText("<h2>SCORE: " + QString::number(score) + "</h1>");
    scoreLabel->setStyleSheet("color: white; font-weight: 900;");
    scoreLabel->setGeometry(10, 10, 200, 25);
    scoreLabel->setVisible(false);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(5);
    effect->setColor(QColor("#000000"));
    effect->setOffset(1,1);
    scoreLabel->setGraphicsEffect(effect);

    // add music to QMediaPlaylist to loop infinitely, then play using QMediaPlayer
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/flowerGarden.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(20);
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

    // Enemy spawning logic
    if (counter == 0) {
        qsrand(time(NULL));
        random = qrand() % 2;

        if (random == 0) {
            obstacles.append(factory->newImage("enemy", 1));
        } else {
            obstacles.append(factory->newImage("enemy", 2));
        }
    }

    // How often to spawn enemies
    if (score < 15) {
        spawnTime = 30 - score;
    } else {
        spawnTime = 15;
    }

    if (counter == spawnTime) {
        counter = 0;
    } else {
        counter++;
    }

    // Enemy movement and cleaning
    for (int i = 0; i < obstacles.size(); ++i) {
        if (obstacles[i]->offscreen()) {
            delete obstacles[i];
            obstacles.removeAt(i);
            score++;
            scoreLabel->setText("<h2>SCORE: " + QString::number(score) + "</h1>");
        }

        obstacles[i]->renderImage(painter);
        obstacles[i]->animate();

        // Death logic
        if (character->intersects(obstacles[i])) {
            timer->stop();
            music->pause();
            dead = true;
            gameOver->setVisible(true);
            QSound::play(":/sounds/gameOver.wav");
        }
    }
}

// event for whenever a key is pressed
void Dialog::keyPressEvent(QKeyEvent *event) {

    // when p is pressed and the game has started
    if(event->key() == Qt::Key_P && started && !dead) {

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
        scoreLabel->setVisible(true);
        QSound::play(":/sounds/pause.wav");

        // start the game
        timer->start(4000/config.getStartVel());

    } else if (event->key() == Qt::Key_Space && started && !paused && !dead) {
        character->jump();
    }
}
