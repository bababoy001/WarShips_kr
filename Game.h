#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include "Cell.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    // constructor
    Game(QWidget *parent = NULL);

    // public methods
    void displayMainMenu();

    void attack(Cell* cell);

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



    bool gameMode;
    bool placeMode;

    int zalpMode1;
    int zalpMode2;

    int numShipsPlayer1;
    int numShipsPlayer2;

    int numMinePlayer1;
    int numMinePlayer2;


    bool botMode;

public slots:
    // public slots

private:
    // private mathod
    void createScreenGame();
    void drawGame();
    void hideGame();

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
