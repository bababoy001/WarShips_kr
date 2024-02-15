#include "Game.h"
#include "Button.h"
#include "capitalShip.h"
#include "fuelShip.h"
#include "mine.h"
#include <QSoundEffect>
#include <QTimer>
#include <stdlib.h>
#include "BotLvl2.h"
#include "BotLvl3.h"
#include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widthWindow = 1000;
    heightWindow = 800;

    // set up the scene
    scene = new QGraphicsScene();
    setScene(scene);

    // set up the screen and scene
    setWindowSize(widthWindow,heightWindow);

    // initialize variables
    numShipsPlayer1 = 0;
    numShipsPlayer2 = 0;
    numMinePlayer1 = 0;
    numMinePlayer2 = 0;
    gameMode = false;
    placeMode = false;
    zalpMode1 = 0;
    zalpMode2 = 0;
    botMode = false;
    shipToPlace = NULL;
    widthMapFPS = 6;
    heightMapFPS = 6;
}

void Game::displayMainMenu(){

    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("War Ships"));
    QFont titleFont("comic sens", 50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 50;
    titleText->setPos(txPos, tyPos);
    scene->addItem(titleText);

    // create the play button with friend
    Button* playButtonF = new Button(QString("Play with friend"));
    playButtonF->setPos(200, 450);
    scene->addItem(playButtonF);
    connect(playButtonF, &Button::clicked, this, [=]() {
        displayFreindMenu(QString("PLAYER1"));
    });

    // create the play button vs computer
    Button* playButtonC = new Button(QString("Play vs computer"));
    playButtonC->setPos(600, 450);
    scene->addItem(playButtonC);
    connect(playButtonC, &Button::clicked, this, [=]() {
        displayBotMenu();
    });

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 600;
    quitButton->setPos(qxPos, qyPos);
    scene->addItem(quitButton);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    // add images
    QGraphicsPixmapItem* imageHumans = new QGraphicsPixmapItem(QPixmap(QString(":/images/Images/humans.png")));
    imageHumans->setPos(225,250);
    scene->addItem(imageHumans);

    QGraphicsPixmapItem* imageComputer = new QGraphicsPixmapItem(QPixmap(QString(":/images/Images/computer.png")));
    imageComputer->setPos(625,250);
    scene->addItem(imageComputer);
}

void Game::attack(Cell *cell){

    // find the map where this cell is from
    bool cellInFirstMap = false;
    bool cellInSecondMap = false;

    for(int i = 0, n = getWidthMap(); i < n; i++){
        for(int j = 0, n = getHeightMap(); j < n; j++){
            if(player1Map[i][j] == cell){
                cellInFirstMap = true;
                break;
            }
            else if(player2Map[i][j] == cell){
                cellInSecondMap = true;
                break;
            }
        }
    }

    // add sound effect
    QSoundEffect *sound = new QSoundEffect(this);
    sound->setVolume(0.7);
    sound->play();

    // attack enemy map
    if(((cellInFirstMap) && (getWhosTurn() == QString("PLAYER2"))) || ((cellInSecondMap) && (getWhosTurn() == QString("PLAYER1")))){
        // if cell already Hit or Miss
        if(cell->isHit || cell->isMiss){
            if(botMode && getWhosTurn() == QString("PLAYER1")){
                bot->botAttack();
            }
            return;
        }
        // if Miss
        else if(!cell->isHit && !cell->isMiss && !cell->isShip){
            // hide whos Turn
            textPlayer1->setVisible(false);
            textPlayer2->setVisible(false);

            // play sound if Miss
            sound->setSource(QUrl("qrc:/music/Music/soundMiss.wav"));
            sound->play();

            // change turn
            if(getWhosTurn() == QString("PLAYER1")){
                setWhosTurn(QString("PLAYER2"));
            }
            else if(getWhosTurn() == QString("PLAYER2")){
                setWhosTurn(QString("PLAYER1"));
            }

            // remember whos turn
            QString rememberPlayer = getWhosTurn();

            // block map for time
            setWhosTurn(QString("NOONE"));

            QTimer::singleShot(1400, this, [=](){

                // draw miss cross
                cell->drawCross();

                // show whos Turn
                textPlayer1->setVisible(true);
                textPlayer2->setVisible(true);

                setWhosTurn(rememberPlayer);

                // draw zalp message
                if(zalpMode1){
                    setWhosTurn(QString("PLAYER1"));
                    QString allowedMissesText = QString("\nThe turn is passed to Player 1 and he has the right to %1 misses").arg(zalpMode1);
                    returnFire->setPlainText("Player 2 has destroyed an enemy Сapital ship." + allowedMissesText);
                    returnFire->setVisible(true);
                    returnFire->setPos(this->width()/2 -  returnFire->boundingRect().width()/2, 100 + (getHeightMap()*40) + 10);
                    zalpMode1--;
                }
                else{
                    returnFire->setVisible(false);
                }
                if(zalpMode2){
                    setWhosTurn(QString("PLAYER2"));
                    QString allowedMissesText = QString("\nThe turn is passed to Player 2 and he has the right to %1 misses").arg(zalpMode2);
                    returnFire->setPlainText("Player 1 has destroyed an enemy Сapital ship." + allowedMissesText);
                    returnFire->setVisible(true);
                    returnFire->setPos(this->width()/2 -  returnFire->boundingRect().width()/2, 100 + (getHeightMap()*40) + 10);
                    zalpMode2--;
                }

                if(botMode && getWhosTurn() == QString("PLAYER1")){
                    bot->botAttack();
                }
            });
            cell->isMiss = true;
        }
        // if Hit
        else if(!cell->isHit && !cell->isMiss && cell->isShip){
            // hide whos Turn
            textPlayer1->setVisible(false);
            textPlayer2->setVisible(false);

            // play sound if Hit
            sound->setSource(QUrl("qrc:/music/Music/soundHit.wav"));
            sound->play();

            QString rememberPlayer = getWhosTurn();
            setWhosTurn(QString("NOONE"));
            QTimer::singleShot(1400, this, [=](){

                // draw hit blast
                cell->drawBlast1();

                // show whos Turn
                textPlayer1->setVisible(true);
                textPlayer2->setVisible(true);

                setWhosTurn(rememberPlayer);


                // check is ship is destroy
                checkShipInHit(cell);

                if(getWhosTurn()  == QString("PLAYER1") && zalpMode2>0){
                    setWhosTurn(QString("PLAYER2"));
                    QString allowedMissesText = QString("\nThe turn is passed to Player 2 and he has the right to %1 misses").arg(zalpMode2+1);
                    returnFire->setPlainText("Player 1 has destroyed an enemy Сapital ship." + allowedMissesText);
                    returnFire->setVisible(true);
                    returnFire->setPos(this->width()/2 -  returnFire->boundingRect().width()/2, 100 + (getHeightMap()*40) + 10);
                }
                else if(getWhosTurn()  == QString("PLAYER2") && zalpMode1>0){
                    setWhosTurn(QString("PLAYER1"));
                    QString allowedMissesText = QString("\nThe turn is passed to Player 1 and he has the right to %1 misses").arg(zalpMode1+1);
                    returnFire->setPlainText("Player 2 has destroyed an enemy Сapital ship." + allowedMissesText);
                    returnFire->setVisible(true);
                    returnFire->setPos(this->width()/2 -  returnFire->boundingRect().width()/2, 100 + (getHeightMap()*40) + 10);
                }

                if(botMode && getWhosTurn() == QString("PLAYER1") && numShipsPlayer2 != 0 && numShipsPlayer1 != 0){
                    bot->botAttack();
                }
            });
            cell->isHit = true;
        }
    }
}

void Game::pickUpShip(Ship *ship){
    // picks up the specified ship
    if(shipToPlace == NULL){
        shipToPlace = ship;
        return;
    }
}

void Game::placeSpecifiedShip(Cell* cell){

    // initialize coordinates
    int x = -1;
    int y = -1;

    // make wrongPlace message
    int txPos = 0;
    int tyPos = 0;

    if(shipToPlace->getOwner() == QString("PLAYER1")){
        txPos = 50 + (getWidthMap()*40)/2 - wrongPlace->boundingRect().width()/2;
        tyPos = 100 + (getHeightMap() + 6)*40 + 10;
        for(size_t i = 0, n = getWidthMap(); i < n; i++){
            for(size_t j = 0, n = getHeightMap(); j < n; j++){
                if(player1Map[i][j] == cell){
                    x = i;
                    y = j;
                }
            }
        }
    }
    else if(shipToPlace->getOwner() == QString("PLAYER2")){
        txPos = 150 + (getWidthMap()*40) + (getWidthMap()*40)/2 - wrongPlace->boundingRect().width()/2;
        tyPos = 100 + (getHeightMap() + 6)*40 + 10;
        for(size_t i = 0, n = getWidthMap(); i < n; i++){
            for(size_t j = 0, n = getHeightMap(); j < n; j++){
                if(player2Map[i][j] == cell){
                    x = i;
                    y = j;
                }
            }
        }
    }
    wrongPlace->setPos(txPos, tyPos);


    // find coordinates which sutisfy the rules

    // check coordinates
    if(!isPlaceForShip(x,y,shipToPlace, shipToPlace->getOwner())){
        // if coordinates not for ship - show wrongPlace and play sound (dont place ship)
        QSoundEffect *music = new QSoundEffect(this);
        music->setSource(QUrl("qrc:/music/Music/error.wav"));
        music->setVolume(0.1);
        music->play();

        wrongPlace->setVisible(true);
        return;
    }

    // place ship if coordinates sutisfy the rules
    addShipToVector(shipToPlace, shipToPlace->getOwner());

    placeShip(shipToPlace->getOwner());
    scene->removeItem(shipToPlace);
    shipToPlace = NULL;
    wrongPlace->setVisible(false);
}

bool Game::isCellInMap(int x, int y){
    // check coord to size map
    return (x >= 0) && (y >= 0) && (x < getWidthMap()) && (y < getHeightMap());
}

void Game::checkShipInHit(Cell *cell){

    // find in which ship you hit
    Ship* temp_ship;
    temp_ship = cellToShip[cell];

    // countHit++
    temp_ship->increaseCountHit();

    // check is ship destroyed
    if(temp_ship->getCountHit() == temp_ship->getNumDeck()){
        temp_ship->destroyShip(getWhosTurn());

        if(botMode && hitedCell.size() != 0){
            // make vector of hited cells
            checkHitedShips();
        }
    }

    // end game if ships run out
    if(numShipsPlayer2 == 0){
        displayGameOverWindow(QString("First player win"));
    }
    else if(numShipsPlayer1 == 0){
        displayGameOverWindow(QString("Second player win"));
    }
}

void Game::mouseMoveEvent(QMouseEvent *event){
    // if there is a shipToPlase, then make it follow the mouse
    if(shipToPlace){
        shipToPlace->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent *event){
    // make right click to change horizontal
    if(event->button() == Qt::RightButton){
        if(shipToPlace){
            horizontal = !horizontal;
            shipToPlace->setHorizontal(horizontal);
            shipToPlace->makeSkinShip(true);
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}

QString Game::getWhosTurn(){
    return whosTurn_;
}

int Game::getWidthMap(){
    return widthMap;
}

int Game::getHeightMap(){
    return heightMap;
}

void Game::setWindowSize(int width, int height){
    // set window width and height
    widthWindow = width;
    heightWindow = height;

    // set size of screen
    setFixedSize(width, height);

    // set size of scene
    scene->setSceneRect(0,0,width, height);
}

void Game::setMapSize(int rows, int columns){
    // resize map
    widthMap = rows;
    heightMap = columns;
}

void Game::setWhosTurn(QString player){
    // change the QString
    whosTurn_ = player;

    // change the color of players
    if(player == QString("PLAYER1")){
        // set textPlayer1 green, what meen his turn
        textPlayer1->setDefaultTextColor(QColor(Qt::green));

        // set textPlayer2 black
        textPlayer2->setDefaultTextColor(QColor(Qt::black));
    }
    else if(player == QString("PLAYER2")){
        // set textPlayer2 green, what meen his turn
        textPlayer2->setDefaultTextColor(QColor(Qt::green));

        // set textPlayer1 black
        textPlayer1->setDefaultTextColor(QColor(Qt::black));
    }
}

void Game::start(){
    // delete all menu
    for(int i = 0; i < itemToDelete.size(); i++){
        scene->removeItem(itemToDelete[i]);
        delete itemToDelete[i];
    }
    itemToDelete.clear();

    // draw game
    drawGame();

    // hide ships

    if(botMode){
        hideShips(QString("PLAYER1"));
    }
    else{
        hideShips(QString("PLAYER1"));
        hideShips(QString("PLAYER2"));
    }

    placeMode = false;
    gameMode = true;

    setWhosTurn(QString("PLAYER2"));
}

void Game::displayFreindMenu(QString player){

    if(player == QString("PLAYER1")){
        // clear the screen
        scene->clear();

        // enter size of map
        enterSizeMap();

        // create all game
        createScreenGame();
    }

    else if(player == QString("PLAYER2")){
        for(int i = 0; i < itemToDelete.size(); i++){
            scene->removeItem(itemToDelete[i]);
            delete itemToDelete[i];
        }
        itemToDelete.clear();
        hideGame();
        hideShips("PLAYER1");
    }

    // create text
    QGraphicsTextItem* playerText = new QGraphicsTextItem(player);
    QFont fontPlayer("comic sens", 25);
    playerText->setFont(fontPlayer);
    int txPos = this->width()/2 - playerText->boundingRect().width()/2;
    int tyPos = 50;
    playerText->setPos(txPos, tyPos);
    scene->addItem(playerText);

    // create the random button
    Button* random = new Button(QString("Ramdom place ships"));
    int rxPos = this->width()/2 - random->boundingRect().width()/2;
    int ryPos = 275;
    random->setPos(rxPos, ryPos);
    scene->addItem(random);
    connect(random, &Button::clicked, this, [=]() {
        setPlaceMode(player, true);
    });

    // create the notRandom button
    Button* notRandom = new Button(QString("Manual placement of ships"));
    int nrxPos = this->width()/2 - notRandom->boundingRect().width()/2;
    int nryPos = 350;
    notRandom->setPos(nrxPos, nryPos);
    scene->addItem(notRandom);
    connect(notRandom, &Button::clicked, this, [=]() {
        setPlaceMode(player, false);
    });

    itemToDelete.push_back(playerText);
    itemToDelete.push_back(random);
    itemToDelete.push_back(notRandom);
}

void Game::displayBotMenu(){

    scene->clear();

    // enter size of map
    enterSizeMap();

    // create text
    QGraphicsTextItem* text = new QGraphicsTextItem(QString("Сhoose the difficulty level of the bot"));
    QFont fontPlayer("comic sens", 25);
    text->setFont(fontPlayer);
    int txPos = this->width()/2 - text->boundingRect().width()/2;
    int tyPos = 50;
    text->setPos(txPos, tyPos);
    scene->addItem(text);

    // create ease bot
    Button* easeBot = new Button(QString("Ease"));
    int exPos = this->width()/2 - easeBot->boundingRect().width()/2;
    int eyPos = 275;
    easeBot->setPos(exPos, eyPos);
    scene->addItem(easeBot);
    connect(easeBot, &Button::clicked, this, [=]() {
        setBotMode(1);
    });

    // create medium bot
    Button* mediumBot = new Button(QString("Medium"));
    int mxPos = this->width()/2 - mediumBot->boundingRect().width()/2;
    int myPos = 375;
    mediumBot->setPos(mxPos, myPos);
    scene->addItem(mediumBot);
    connect(mediumBot, &Button::clicked, this, [=]() {
        setBotMode(2);
    });

    // create hard bot
    Button* hardBot = new Button(QString("Hard"));
    int hxPos = this->width()/2 - hardBot->boundingRect().width()/2;
    int hyPos = 475;
    hardBot->setPos(hxPos, hyPos);
    scene->addItem(hardBot);
    connect(hardBot, &Button::clicked, this, [=]() {
        setBotMode(3);
    });
}

void Game::setBotMode(int lvlBot){
    botMode = true;
    switch (lvlBot) {
    case 1:
        bot = new Bot();
        break;
    case 2:
        bot = new BotLvl2();
        break;
    case 3:
        bot = new BotLvl3();
        break;
    }

    scene->clear();

    createScreenGame();

    setPlaceMode(QString("PLAYER1"), true);

    displayFreindMenu(QString("PLAYER2"));
}

void Game::setPlaceMode(QString player, bool random){

    for(int i = 0; i < itemToDelete.size(); i++){
        scene->removeItem(itemToDelete[i]);
        delete itemToDelete[i];
    }
    itemToDelete.clear();

    placeMode = true;
    gameMode = false;
    drawGame();

    if(player == QString("PLAYER1")){
        if(random){
            createRandomShips(QString("PLAYER1"));
        }
        else if(!random){
            createShips(QString("PLAYER1"));
        }
    }
    else if(player == QString("PLAYER2")){
        if(random){
            createRandomShips(QString("PLAYER2"));
        }
        else if(!random){
            createShips(QString("PLAYER2"));
        }
    }
}

void Game::displayGameOverWindow(QString textToDisplay){
    // disable all scene items
    for(size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    // draw background
    QGraphicsRectItem * panel = new QGraphicsRectItem(0,0,widthWindow, heightWindow);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    panel->setBrush(brush);
    panel->setOpacity(0.65);
    scene->addItem(panel);


    // draw menu
    QGraphicsRectItem * panel2 = new QGraphicsRectItem(widthWindow/2 - 150 , 0, 300, 300);
    QBrush brush2;
    brush2.setStyle(Qt::SolidPattern);
    brush2.setColor(Qt::lightGray);
    panel2->setBrush(brush2);
    scene->addItem(panel2);

    // create playAgain button
    Button* playAgain = new Button(QString("Play Again"));
    playAgain->setPos(widthWindow/2 - 100, 100);
    scene->addItem(playAgain);
    connect(playAgain,SIGNAL(clicked()),this,SLOT(restartGame()));

    // create quit button
    Button* quit = new Button(QString("Quit"));
    quit->setPos(widthWindow/2 - 100, 200);
    scene->addItem(quit);
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));

    // create text annoucning winner
    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    QFont fontPlayer("comic sens", 25);
    overText->setFont(fontPlayer);
    int txPos = this->width()/2 - overText->boundingRect().width()/2;
    int tyPos = 10;
    overText->setPos(txPos, tyPos);
    overText->setDefaultTextColor(QColor(Qt::green));
    scene->addItem(overText);
}

void Game::restartGame(){
    // initialize variables as default

    numShipsPlayer1 = 0;
    numShipsPlayer2 = 0;

    numMinePlayer1 = 0;
    numMinePlayer2 = 0;

    gameMode = false;
    placeMode = false;
    zalpMode1 = 0;
    zalpMode2 = 0;
    botMode = false;
    shipToPlace = NULL;
    widthMapFPS = 6;
    heightMapFPS = 6;

    // clear some stuff
    player1Ship.clear();
    player2Ship.clear();

    cellToShip.clear();

    textLetters.clear();
    textNumbers.clear();

    player1Map.clear();
    player2Map.clear();

    itemToDelete.clear();

    hitedCell.clear();
    hitedShips.clear();

    setWindowSize(1000,800);

    scene->clear();

    displayMainMenu();
}

void Game::enterSizeMap(){
    // enter Width and Height
    QLabel *label1 = new QLabel("Width (from 8 to 22):");
    QLabel *label2 = new QLabel("Height (from 8 to 15) :");
    QLineEdit *lineEdit1 = new QLineEdit;
    QLineEdit *lineEdit2 = new QLineEdit;

    // make buttons
    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Close");

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addWidget(label1);
    mainLayout->addWidget(lineEdit1);
    mainLayout->addWidget(label2);
    mainLayout->addWidget(lineEdit2);
    mainLayout->addLayout(buttonLayout);

    QWidget *parent = nullptr;

    QDialog dialog(parent);
    dialog.setLayout(mainLayout);

    // connect signals and slots
    QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // if player enter size map
    if (dialog.exec() == QDialog::Accepted) {
        if (lineEdit1->text().toInt() >= 8 && lineEdit1->text().toInt() <= 22 && lineEdit2->text().toInt() >=8 && lineEdit2->text().toInt() <=15) {
            setMapSize(lineEdit1->text().toInt(),lineEdit2->text().toInt());
        } else {
            enterSizeMap();
        }
    }
    // if player close dialog
    else {
        setMapSize(10,10);
    }
}


void Game::createScreenGame(){
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

void Game::hideShips(QString player){
    // hide ships
    if(player == QString("PLAYER1")){
        for(int i = 0; i < player1Ship.size(); i++){
            for(int j = 0; j < player1Ship[i]->coorXY.size(); j++){
                player1Map[player1Ship[i]->coorXY[j].first][player1Ship[i]->coorXY[j].second]->pixItem->setVisible(false);
            }
        }
    }
    else if(player == QString("PLAYER2")){
        for(int i = 0; i < player2Ship.size(); i++){
            for(int j = 0; j < player2Ship[i]->coorXY.size(); j++){
                player2Map[player2Ship[i]->coorXY[j].first][player2Ship[i]->coorXY[j].second]->pixItem->setVisible(false);
            }
        }
    }
}

void Game::createRandomShips(QString player){
    // get default variables
    initializeVar();

    // make ships
    while (currntShipsDeck < max_deck) {
        Ship* temp_ship;
        horizontal = rand() % 2;
        temp_size_ship = 1 + rand() % max_length_ship;
        while ((temp_size_ship + currntShipsDeck) > max_deck){
            temp_size_ship--;
        }
        if (fuelNum) {
            temp_ship = new fuelShip();
            temp_size_ship = 4;
            fuelNum--;
        }
        else if (capitalNum) {
            temp_ship = new capitalShip();
            temp_size_ship = 4;
            capitalNum--;
        }
        else{
            temp_ship = new Ship();
        }

        temp_ship->setHorizontal(horizontal);
        temp_ship->setNameShip(nameShip);
        temp_ship->setNumDeck(temp_size_ship);
        temp_ship->setOwner(player);
        temp_ship->makeSkinShip(true);

        randomPlaceShip(temp_ship, player);

        currntShipsDeck += temp_size_ship;
    }

    // make mines
    while (mineNum) {
        Ship* temp_ship = new mine();
        horizontal = rand() % 2;
        temp_size_ship = 1;

        temp_ship->setHorizontal(horizontal);
        temp_ship->setNumDeck(temp_size_ship);
        temp_ship->setOwner(player);
        temp_ship->makeSkinShip(true);

        randomPlaceMine(temp_ship, player);

        mineNum--;
    }

    // start or change player
    if(player == QString("PLAYER1")){
        displayFreindMenu("PLAYER2");
    }
    else if(player == QString("PLAYER2")){
        start();
    }
}

void Game::randomPlaceShip(Ship *temp_ship, QString player){
    // get random coordinates
    int x = rand() % widthMap;
    int y = rand() % heightMap;

    // check coordinates
    if(!isPlaceForShip(x,y,temp_ship, player)){
        // if coordinates not for ship - try new coord
        randomPlaceShip(temp_ship, player);
        return;
    }

    // add to player1 or player2 vector
    addShipToVector(temp_ship, player);
}

void Game::randomPlaceMine(Ship *temp_ship, QString player){
    // get random coordinates
    int x = rand() % widthMap;
    int y = rand() % heightMap;

    // check coordinates
    while(!isPlaceForShip(x,y,temp_ship, player)){
        // if coordinates not for mine - try new coord
        randomPlaceMine(temp_ship, player);
        return;
    }

    // add to player1 or player2 vector
    if(player == QString("PLAYER1")){
        temp_ship->cell1->setPos(player1Map[temp_ship->coorXY[0].first][temp_ship->coorXY[0].second]->pos());
        scene->removeItem(player1Map[temp_ship->coorXY[0].first][temp_ship->coorXY[0].second]);
        player1Map[temp_ship->coorXY[0].first][temp_ship->coorXY[0].second] = temp_ship->cell1;
        scene->addItem(player1Map[temp_ship->coorXY[0].first][temp_ship->coorXY[0].second]);
        cellToShip[temp_ship->cell1] = temp_ship;

        player1Ship.push_back(temp_ship);
    }
    else if(player == QString("PLAYER2")){
        temp_ship->cell1->setPos(player2Map[temp_ship->coorXY[0].first][temp_ship->coorXY[0].second]->pos());
        scene->removeItem(player2Map[temp_ship->coorXY[0].first][temp_ship->coorXY[0].second]);
        player2Map[temp_ship->coorXY[0].first][temp_ship->coorXY[0].second] = temp_ship->cell1;
        scene->addItem(player2Map[temp_ship->coorXY[0].first][temp_ship->coorXY[0].second]);
        cellToShip[temp_ship->cell1] = temp_ship;

        player2Ship.push_back(temp_ship);
    }
}

void Game::createShips(QString player){
    // get default variables
    initializeVar();

    // make one more map to place ships
    makeMapPlaceShip(player);

    // make one ship
    placeShip(player);
}

void Game::placeShip(QString player){

    // check decks of ship
    if(currntShipsDeck < max_deck) {
        Ship* temp_ship;
        horizontal = rand() % 2;
        temp_size_ship = 1 + rand() % max_length_ship;
        while ((temp_size_ship + currntShipsDeck) > max_deck){
            temp_size_ship--;
        }

        if (fuelNum) {
            temp_ship = new fuelShip();
            temp_size_ship = 4;
            fuelNum--;
        }
        else if (capitalNum) {
            temp_ship = new capitalShip();
            temp_size_ship = 4;
            capitalNum--;
        }
        else{
            temp_ship = new Ship();
        }

        temp_ship->setHorizontal(horizontal);
        temp_ship->setNameShip(nameShip);
        temp_ship->setNumDeck(temp_size_ship);
        temp_ship->setOwner(player);
        temp_ship->makeSkinShip(true);

        temp_ship->setPos(mapForPlaceShip[1][1]->x()+5,mapForPlaceShip[1][1]->y()+5);
        scene->addItem(temp_ship);

        currntShipsDeck += temp_size_ship;
    }
    else if(mineNum) {

        // make mines
        Ship* temp_ship = new mine();
        horizontal = rand() % 2;
        temp_size_ship = 1;

        temp_ship->setHorizontal(horizontal);
        temp_ship->setNumDeck(temp_size_ship);
        temp_ship->setOwner(player);
        temp_ship->makeSkinShip(true);

        temp_ship->setPos(mapForPlaceShip[1][1]->x()+5,mapForPlaceShip[1][1]->y()+5);
        scene->addItem(temp_ship);

        if(player == QString("PLAYER1")){
            numMinePlayer1++;
            numShipsPlayer1--;
        }
        else if(player == QString("PLAYER2")){
            numMinePlayer2++;
            numShipsPlayer2--;
        }

        mineNum--;
    }
    else{
        // delete mapForPlaceShip
        for(size_t i = 0, n = widthMapFPS; i < n; i++){
            for(size_t j = 0, n = heightMapFPS; j < n; j++){
                scene->removeItem(mapForPlaceShip[i][j]);
                delete mapForPlaceShip[i][j];
            }
        }

        // create ready button
        Button* Ready = new Button(QString("Ready"));
        int nrxPos = this->width()/2 - Ready->boundingRect().width()/2;
        int nryPos = this->height() - 100;
        if(player == QString("PLAYER1")){
            Ready->setPos(nrxPos, nryPos);
            scene->addItem(Ready);
            itemToDelete.push_back(Ready);
            connect(Ready, &Button::clicked, this, [=]() {
                displayFreindMenu("PLAYER2");
            });
        }
        else if(player == QString("PLAYER2")){
            Ready->setPos(nrxPos, nryPos);
            scene->addItem(Ready);
            itemToDelete.push_back(Ready);
            connect(Ready, &Button::clicked, this, [=]() {
                start();
            });
        }
    }
}

void Game::makeMapPlaceShip(QString player){
    // change size of vector mapForPlaceShip
    mapForPlaceShip.resize(widthMapFPS);
    for (int i = 0; i < widthMapFPS; ++i) {
        mapForPlaceShip[i].resize(heightMapFPS);
    }

    // add cells to mapForPlaceShip
    int firstCellPosX = 0;
    int firstCellPosY = 0;
    if(player == QString("PLAYER1")){
        firstCellPosX = 50 + getWidthMap()*20 - widthMapFPS*20;
        firstCellPosY = 50 + getHeightMap()*40 + 45;
    }
    else if(player == QString("PLAYER2")){
        firstCellPosX = 150 + getWidthMap()*60 - widthMapFPS*20;
        firstCellPosY = 50 + getHeightMap()*40 + 45;
    }

    for(size_t i = 0, n = widthMapFPS; i < n; i++){
        for(size_t j = 0, n = heightMapFPS; j < n; j++){
            Cell* cell = new Cell();
            cell->setPos(firstCellPosX + 40*i, firstCellPosY + 40*j);
            cell->setPlaceMode();
            mapForPlaceShip[i][j] = cell;
            scene->addItem(cell);
        }
    }
}

void Game::initializeVar(){
    // initialize variables to deaufolt
    max_length_ship = 4;
    max_deck = int(getWidthMap() * getHeightMap() * 0.2);
    temp_size_ship = 1;
    horizontal = false;
    currntShipsDeck = 0;
    nameShip = QString("Ship");
    fuelNum = 1;
    capitalNum = 1;
    mineNum = int(getWidthMap() * getHeightMap() * 0.02);
}

void Game::addShipToVector(Ship *temp_ship, QString player){
    // add to player1 or player2 vector
    if(player == QString("PLAYER1")){
        for (int i = 0; i < temp_ship->getNumDeck(); i++) {
            switch (i) {
            case 0:
                temp_ship->cell1->setPos(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]->pos());
                scene->removeItem(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second] = temp_ship->cell1;
                scene->addItem(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                cellToShip[temp_ship->cell1] = temp_ship;
                break;
            case 1:
                temp_ship->cell2->setPos(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]->pos());
                scene->removeItem(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second] = temp_ship->cell2;
                scene->addItem(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                cellToShip[temp_ship->cell2] = temp_ship;
                break;
            case 2:
                temp_ship->cell3->setPos(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]->pos());
                scene->removeItem(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second] = temp_ship->cell3;
                scene->addItem(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                cellToShip[temp_ship->cell3] = temp_ship;
                break;
            case 3:
                temp_ship->cell4->setPos(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]->pos());
                scene->removeItem(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second] = temp_ship->cell4;
                scene->addItem(player1Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                cellToShip[temp_ship->cell4] = temp_ship;
                break;
            }
        }
        player1Ship.push_back(temp_ship);
        numShipsPlayer1++;
    }
    else if(player == QString("PLAYER2")){
        for (int i = 0; i < temp_ship->getNumDeck(); i++) {
            switch (i) {
            case 0:
                temp_ship->cell1->setPos(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]->pos());
                scene->removeItem(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second] = temp_ship->cell1;
                scene->addItem(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                cellToShip[temp_ship->cell1] = temp_ship;
                break;
            case 1:
                temp_ship->cell2->setPos(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]->pos());
                scene->removeItem(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second] = temp_ship->cell2;
                scene->addItem(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                cellToShip[temp_ship->cell2] = temp_ship;
                break;
            case 2:
                temp_ship->cell3->setPos(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]->pos());
                scene->removeItem(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second] = temp_ship->cell3;
                scene->addItem(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);

                cellToShip[temp_ship->cell3] = temp_ship;
                break;
            case 3:
                temp_ship->cell4->setPos(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]->pos());
                scene->removeItem(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second] = temp_ship->cell4;
                scene->addItem(player2Map[temp_ship->coorXY[i].first][temp_ship->coorXY[i].second]);
                cellToShip[temp_ship->cell4] = temp_ship;
                break;
            }
        }
        player2Ship.push_back(temp_ship);
        numShipsPlayer2++;
    }
}


bool Game::isPlaceForShip(int x, int y, Ship *temp_ship, QString player){
    bool place = true;

    // check coordinates
    for (int i = 0; i < temp_ship->getNumDeck(); i++) {

        // if ship horizontal
        if (temp_ship->getHorizontal()) {
            if (!isCellForShip(x+i, y, player)) {
                place = false;
                break;
            }
            else {
                QPair<int, int> pairXY(x+i, y);
                temp_ship->coorXY.push_back(pairXY);
            }
        }

        // if ship vertical
        else if (!temp_ship->getHorizontal()) {
            if (!isCellForShip(x, y + i, player)) {
                place = false;
                break;
            }
            else {
                QPair<int, int> pairXY(x, y+i);
                temp_ship->coorXY.push_back(pairXY);
            }
        }
    }

    // if wrong coordinates - clear old coordinates
    if (!place) {
        temp_ship->coorXY.clear();
    }
    return place;
}

bool Game::isCellForShip(int x, int y, QString player){
    // create temporary map
    QVector<QVector<Cell*>> currentMap;

    // check whos map
    if(player == QString("PLAYER1")){
        currentMap = player1Map;
    }
    else if(player == QString("PLAYER2")){
        currentMap = player2Map;
    }

    // check is ship can place in this cell
    if (!isCellInMap(x, y) || currentMap[x][y]->isShip) {
        return false;
    }
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (isCellInMap(x + dx, y + dy) && currentMap[x + dx][y + dy]->isShip) {
                return false;
            }
        }
    }
    return true;
}

void Game::checkHitedShips(){

    // make hited cells
    QVector<QPair<Cell*, int>> tempHitedCell = hitedCell;

    hitedCell.clear();
    hitedShips.clear();

    for (int i = 0; i < tempHitedCell.size(); ++i) {
        if(cellToShip[tempHitedCell[i].first]->getCountHit() != cellToShip[tempHitedCell[i].first]->getNumDeck() && hitedShips.indexOf(cellToShip[tempHitedCell[i].first]) == -1){
            // set horizontal if bot hit more then 1 deck
            if(cellToShip[tempHitedCell[i].first]->getCountHit() >=2){
                if(cellToShip[tempHitedCell[i].first]->getHorizontal()){
                    tempHitedCell[i].second = 1;
                }
                else if(!cellToShip[tempHitedCell[i].first]->getHorizontal()){
                    tempHitedCell[i].second = 0;
                }
            }
            hitedCell.push_back(tempHitedCell[i]);
            hitedShips.push_back(cellToShip[tempHitedCell[i].first]);
        }
    }
}
