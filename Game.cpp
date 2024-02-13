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

void Game::createScreenGame()
{
    // change size of maps: player1Map, player2Map
    player1Map.resize(getWidthMap());
    player2Map.resize(getWidthMap());
    for (int i = 0; i < getWidthMap(); ++i) {
        player1Map[i].resize(getHeightMap());
        player2Map[i].resize(getHeightMap());
    }

    // set first coord for map 1
    int firstCellPosXFirstMap = 50;
    int lastCellPosXFirstMap;

    for (size_t i = 0, n = getWidthMap(); i < n; i++) {
        for (size_t j = 0, n = getHeightMap(); j < n; j++) {
            lastCellPosXFirstMap = firstCellPosXFirstMap + 40 * i;

            // add cell to player1Map
            Cell *cell = new Cell();
            cell->setPos(lastCellPosXFirstMap, 50 + 40 * j);
            cell->setVisible(false);
            player1Map[i][j] = cell;
            scene->addItem(cell);
        }
    }

    // set first coord for map 2
    int firstCellPosXSecondMap = lastCellPosXFirstMap + 140;
    int lastCellPosXSecondMap;

    for (size_t i = 0, n = getWidthMap(); i < n; i++) {
        for (size_t j = 0, n = getHeightMap(); j < n; j++) {
            lastCellPosXSecondMap = firstCellPosXSecondMap + 40 * i;

            // add cell to player2Map
            Cell *cell = new Cell();
            cell->setPos(lastCellPosXSecondMap, 50 + 40 * j);
            cell->setVisible(false);
            player2Map[i][j] = cell;
            scene->addItem(cell);
        }
    }

    // resize window to new map size
    int lastPosY = 50 + 40 * getHeightMap();
    int newWindowWidth = int(lastCellPosXSecondMap + 90);
    int newWindowHeight = int(lastPosY + 350);
    setWindowSize(newWindowWidth, newWindowHeight);

    // change size of textLetters
    textLetters.resize(getWidthMap() * 2);

    // add letters above the map
    int firstMapXposLettter = firstCellPosXFirstMap;
    int secondMapXposLettter = firstCellPosXSecondMap;

    for (size_t i = 0, n = getWidthMap(); i < n; i++) {
        char letter = 'a' + i;
        QFont letterFont("comic sens", 17);

        // add letters firstMap
        firstMapXposLettter = firstMapXposLettter + 20;
        QGraphicsTextItem *textLetter1 = new QGraphicsTextItem(QString(letter));
        textLetter1->setFont(letterFont);
        int txPos1 = firstMapXposLettter + 20 * i - textLetter1->boundingRect().width() / 2;
        int tyPos1 = 15;
        textLetter1->setPos(txPos1, tyPos1);
        textLetter1->setVisible(false);
        textLetters[i] = textLetter1;
        scene->addItem(textLetter1);

        // add letters secondMap
        secondMapXposLettter = secondMapXposLettter + 20;
        QGraphicsTextItem *textLetter2 = new QGraphicsTextItem(QString(letter));
        textLetter2->setFont(letterFont);
        int txPos2 = secondMapXposLettter + 20 * i - textLetter2->boundingRect().width() / 2;
        int tyPos2 = 15;
        textLetter2->setPos(txPos2, tyPos2);
        textLetter2->setVisible(false);
        textLetters[i + getWidthMap()] = textLetter2;
        scene->addItem(textLetter2);
    }

    // change size of textNumbers
    textNumbers.resize(getHeightMap() * 2);

    // add the numbers to the left of the map
    int firstMapXposNum = 50;
    int secondMapXposNum = 50;

    for (size_t i = 0, n = getHeightMap(); i < n; i++) {
        QFont numberFont("comic sens", 17);

        // firstMap
        firstMapXposNum = firstMapXposNum + 20;
        QGraphicsTextItem *textNumber1 = new QGraphicsTextItem(QString(QString::number(i + 1)));
        textNumber1->setFont(numberFont);
        int txPos1 = 15;
        int tyPos1 = firstMapXposNum + 20 * i - textNumber1->boundingRect().height() / 2;
        textNumber1->setPos(txPos1, tyPos1);
        textNumber1->setVisible(false);
        textNumbers[i] = textNumber1;
        scene->addItem(textNumber1);

        // secondMap
        secondMapXposNum = secondMapXposNum + 20;
        QGraphicsTextItem *textNumber2 = new QGraphicsTextItem(QString(QString::number(i + 1)));
        textNumber2->setFont(numberFont);
        int txPos2 = firstCellPosXSecondMap - 35;
        int tyPos2 = secondMapXposNum + 20 * i - textNumber2->boundingRect().height() / 2;
        textNumber2->setPos(txPos2, tyPos2);
        textNumber2->setVisible(false);
        textNumbers[i + getHeightMap()] = textNumber2;
        scene->addItem(textNumber2);
    }

    // set font for plaver text
    QFont textPlayerFont("comic sens", 15);

    // set player1 text
    textPlayer1 = new QGraphicsTextItem(QString("First player"));
    textPlayer1->setFont(textPlayerFont);
    int txPos1 = 50 + (getWidthMap() * 40) / 2 - textPlayer1->boundingRect().width() / 2;
    int tyPos1 = 50 + (getHeightMap() * 40) + 10;
    textPlayer1->setPos(txPos1, tyPos1);
    textPlayer1->setVisible(false);
    scene->addItem(textPlayer1);

    // set player2 text
    textPlayer2 = new QGraphicsTextItem(QString("Second player"));
    textPlayer2->setFont(textPlayerFont);
    int txPos2 = 150 + (getWidthMap() * 40) + (getWidthMap() * 40) / 2
                 - textPlayer2->boundingRect().width() / 2;
    int tyPos2 = 50 + (getHeightMap() * 40) + 10;
    textPlayer2->setPos(txPos2, tyPos2);
    textPlayer2->setVisible(false);
    scene->addItem(textPlayer2);

    // set wrongPlace text
    wrongPlace = new QGraphicsTextItem(QString("Wrong place, try a new place"));
    wrongPlace->setFont(textPlayerFont);
    wrongPlace->setDefaultTextColor(QColor(Qt::red));
    wrongPlace->setVisible(false);
    scene->addItem(wrongPlace);

    // set returnFire text
    returnFire = new QGraphicsTextItem();
    returnFire->setFont(textPlayerFont);
    returnFire->setDefaultTextColor(QColor(Qt::red));
    returnFire->setVisible(false);
    scene->addItem(returnFire);
}

void Game::drawGame(){
    // show player1 and player2 text
    textPlayer1->setVisible(true);
    textPlayer2->setVisible(true);

    // show maps
    for(size_t i = 0, n = widthMap; i < n; i++){
        for(size_t j = 0, n = heightMap; j < n; j++){
            player1Map[i][j]->setVisible(true);
            player2Map[i][j]->setVisible(true);
        }
    }

    // show letters above the map
    for (size_t i = 0, n = textLetters.size(); i < n; i++) {
        textLetters[i]->setVisible(true);
    }

    // show the numbers to the left of the map
    for (size_t i = 0, n = textNumbers.size(); i < n; i++) {
        textNumbers[i]->setVisible(true);
    }

}

void Game::hideGame(){
    // hide player1 and player2 text
    textPlayer1->setVisible(false);
    textPlayer2->setVisible(false);

    // hide maps
    for(size_t i = 0, n = widthMap; i < n; i++){
        for(size_t j = 0, n = heightMap; j < n; j++){
            player1Map[i][j]->setVisible(false);
            player2Map[i][j]->setVisible(false);
        }
    }

    // hide letters above the map
    for (size_t i = 0, n = textLetters.size(); i < n; i++) {
        textLetters[i]->setVisible(false);
    }

    // hide the numbers to the left of the map
    for (size_t i = 0, n = textNumbers.size(); i < n; i++) {
        textNumbers[i]->setVisible(false);
    }
}
