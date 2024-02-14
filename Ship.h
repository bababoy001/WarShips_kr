#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsPixmapItem>
#include <QPair>
#include "Cell.h"

class Ship: public QGraphicsPixmapItem{
public:
    // constructors
    Ship(QGraphicsItem* parent=NULL);

    // event
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    // public methods
    virtual void makeSkinShip(bool visiable);
    virtual void destroyShip(QString player);

    void increaseCountHit();

    // getters
    int getNumDeck();
    bool getHorizontal();
    int getCountHit();
    QString getNameShip();
    QString getOwner();

    // setters
    void setNumDeck(int number);
    void setNameShip(QString name);
    void setHorizontal(bool hor);
    void setOwner(QString player);

    // public variables
    Cell* cell1;
    Cell* cell2;
    Cell* cell3;
    Cell* cell4;

    QGraphicsPixmapItem *pixItem1;
    QGraphicsPixmapItem *pixItem2;
    QGraphicsPixmapItem *pixItem3;
    QGraphicsPixmapItem *pixItem4;

    QVector<QPair<int, int>> coorXY;

    int numDeck;
    bool horizontal;
    int countHit;
    QString nameShip;
    QString owner;
};

#endif // SHIP_H
