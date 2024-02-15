#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QPair>
#include <QMap>
#include "Cell.h"
#include "Ship.h"
#include "Bot.h"

class Game : public QGraphicsView{
    Q_OBJECT
public:
    // constructor
    Game(QWidget *parent = NULL);

    // public methods
    void displayMainMenu();
    void attack(Cell* cell);
    void pickUpShip(Ship* ship);
    void placeSpecifiedShip(Cell *cell);
    bool isCellInMap(int x, int y);
    void checkShipInHit(Cell* cell);

    // events
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent* event);

    // getters
    QString getWhosTurn();
    int getWidthMap();
    int getHeightMap();

    // setters
    void setWindowSize(int widthWind, int heightWind);
    void setMapSize(int rows, int columns);
    void setWhosTurn(QString player);

    // public variables
    QGraphicsScene* scene;
    QVector<QVector<Cell*>> player1Map;
    QVector<QVector<Cell*>> player2Map;

    QVector<QPair<Cell*, int>> hitedCell;
    QVector<Ship *> hitedShips;

    Ship* shipToPlace;
    bool gameMode;
    bool placeMode;

    int zalpMode1;
    int zalpMode2;

    int numShipsPlayer1;
    int numShipsPlayer2;

    int numMinePlayer1;
    int numMinePlayer2;

    Bot* bot;
    bool botMode;

public slots:
    // public slots
    void start();
    void displayFreindMenu(QString player);
    void displayBotMenu();
    void setBotMode(int lvlBot);
    void setPlaceMode(QString player, bool random);
    void displayGameOverWindow(QString textToDisplay);
    void restartGame();

private:
    // private method
    void enterSizeMap();
    void createScreenGame();
    void drawGame();
    void hideGame();
    void hideShips(QString player);

    void createRandomShips(QString player);
    void randomPlaceShip(Ship* temp_ship, QString player);
    void randomPlaceMine(Ship* temp_ship, QString player);
    void createShips(QString player);
    void placeShip(QString player);
    void makeMapPlaceShip(QString player);
    void initializeVar();
    void addShipToVector(Ship* temp_ship, QString player);

    bool isPlaceForShip(int x, int y, Ship* temp_ship, QString player);
    bool isCellForShip(int x, int y, QString player);

    void checkHitedShips();

    // private attributes
    int widthWindow;
    int heightWindow;

    int widthMap;
    int heightMap;

    int widthMapFPS;
    int heightMapFPS;

    int max_length_ship;
    int max_deck;
    int temp_size_ship;
    bool horizontal;
    int currntShipsDeck;
    int fuelNum;
    int capitalNum;
    int mineNum;
    QString nameShip;


    QVector<QVector<Cell*>> mapForPlaceShip;
    QVector<Ship *> player1Ship;
    QVector<Ship *> player2Ship;

    QMap<Cell*, Ship*> cellToShip;

    QString whosTurn_;

    QGraphicsTextItem* textPlayer1;
    QGraphicsTextItem* textPlayer2;

    QGraphicsTextItem* wrongPlace;
    QGraphicsTextItem* returnFire;

    QVector<QGraphicsTextItem*> textLetters;
    QVector<QGraphicsTextItem*> textNumbers;

    QVector<QGraphicsItem*> itemToDelete;
};

#endif // GAME_H
