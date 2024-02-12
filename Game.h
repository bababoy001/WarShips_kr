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

    // getters
    QString getWhosTurn();
    int getWidthMap();
    int getHeightMap();

    // setters
    void setWindowSize(int widthWind, int heightWind);
    void setMapSize(int rows, int columns);
    void setWhosTurn(QString player);

    // public variables
    QGraphicsScene *scene;
    QVector<QVector<Cell*>> player1Map;
    QVector<QVector<Cell*>> player2Map;

public slots:
    // public slots

private:
    // private mathod
    void createScreenGame();

    // private attributes
    int widthWindow;
    int heightWindow;

    int widthMap;
    int heightMap;

    int widthMapFPS;
    int heightMapFPS;

    QString whosTurn_;

    QGraphicsTextItem *textPlayer1;
    QGraphicsTextItem *textPlayer2;

    QGraphicsTextItem* wrongPlace;
    QGraphicsTextItem* returnFire;

    QVector<QGraphicsTextItem *> textLetters;
    QVector<QGraphicsTextItem *> textNumbers;
};

#endif // GAME_H
