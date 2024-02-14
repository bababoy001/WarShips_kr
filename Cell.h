#ifndef CELL_H
#define CELL_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>

#include <QGraphicsPixmapItem>

class Cell : public QGraphicsItemGroup{
public:
    // constructors
    Cell(QGraphicsItem *parent = NULL);

    // public methods
    void drawCross();
    void drawBlast1();
    void drawBlast2();
    void setPlaceMode();

    // setters
    void setImage(QGraphicsPixmapItem *pix);

    // events

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    // public variables
    bool isShip;
    bool isMiss;
    bool isHit;
    bool isCellForPlace;
    QGraphicsPixmapItem *pixItem;

private:
    // private variables
    QGraphicsRectItem *square;
    QGraphicsLineItem *cross1;
    QGraphicsLineItem *cross2;
    QGraphicsPixmapItem *blast1;
    QGraphicsPixmapItem *blast2;
};

#endif // CELL_H
