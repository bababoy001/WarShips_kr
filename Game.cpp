#include "Game.h"
#include "Button.h"

Game::Game(QWidget *parent)
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widthWindow = 1000;
    heightWindow = 800;

    // set up the scene
    scene = new QGraphicsScene();
    setScene(scene);

    // set up the screen and scene
    setWindowSize(widthWindow, heightWindow);
}

void Game::displayMainMenu()
{
    // create the title text
    QGraphicsTextItem *titleText = new QGraphicsTextItem(QString("War Ships"));
    QFont titleFont("comic sens", 50);
    titleText->setFont(titleFont);
    int txPos = this->width() / 2 - titleText->boundingRect().width() / 2;
    int tyPos = 50;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    // create the play button with friend
    Button *playButtonF = new Button(QString("Play with friend"));
    playButtonF->setPos(200, 450);
    scene->addItem(playButtonF);

    // create the play button vs computer
    Button *playButtonC = new Button(QString("Play vs computer"));
    playButtonC->setPos(600, 450);
    scene->addItem(playButtonC);

    // create the quit button
    Button *quitButton = new Button(QString("Quit"));
    int qxPos = this->width() / 2 - quitButton->boundingRect().width() / 2;
    int qyPos = 600;
    quitButton->setPos(qxPos, qyPos);
    scene->addItem(quitButton);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    // add images
    QGraphicsPixmapItem *imageHumans = new QGraphicsPixmapItem(
        QPixmap(QString(":/images/Images/humans.png")));
    imageHumans->setPos(225, 250);
    scene->addItem(imageHumans);

    QGraphicsPixmapItem *imageComputer = new QGraphicsPixmapItem(
        QPixmap(QString(":/images/Images/computer.png")));
    imageComputer->setPos(625, 250);
    scene->addItem(imageComputer);
}

QString Game::getWhosTurn()
{
    return whosTurn_;
}

int Game::getWidthMap()
{
    return widthMap;
}

int Game::getHeightMap()
{
    return heightMap;
}

void Game::setWindowSize(int width, int height)
{
    // set window width and height
    widthWindow = width;
    heightWindow = height;

    // set size of screen
    setFixedSize(width, height);

    // set size of scene
    scene->setSceneRect(0, 0, width, height);
}

void Game::setMapSize(int rows, int columns)
{
    // resize map
    widthMap = rows;
    heightMap = columns;
}

void Game::setWhosTurn(QString player)
{
    // change the QString
    whosTurn_ = player;

    // change the color of players
    if (player == QString("PLAYER1")) {
        // set textPlayer1 green, what meen his turn
        textPlayer1->setDefaultTextColor(QColor(Qt::green));

        // set textPlayer2 black
        textPlayer2->setDefaultTextColor(QColor(Qt::black));
    } else if (player == QString("PLAYER2")) {
        // set textPlayer2 green, what meen his turn
        textPlayer2->setDefaultTextColor(QColor(Qt::green));

        // set textPlayer1 black
        textPlayer1->setDefaultTextColor(QColor(Qt::black));
    }
}
