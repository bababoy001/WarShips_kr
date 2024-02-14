#include "Cell.h"
#include "Game.h"
#include <QSoundEffect>
#include <QPointF>

extern Game* game;

Cell::Cell(QGraphicsItem *parent): QGraphicsItemGroup(parent){
    // draw cell
    square = new QGraphicsRectItem(0, 0, 40, 40);
    addToGroup(square);

    // draw ships
    pixItem = new QGraphicsPixmapItem();

    // draw blast
    blast1 = new QGraphicsPixmapItem();
    blast2 = new QGraphicsPixmapItem();

    // draw cross
    cross1 = new QGraphicsLineItem(10, 10, 30, 30);
    cross2 = new QGraphicsLineItem(10, 30, 30, 10);

    // change color and width of cross
    QPen pen(Qt::black);
    pen.setWidth(3);
    cross1->setPen(pen);
    cross2->setPen(pen);
    addToGroup(cross1);
    addToGroup(cross2);
    cross1->setVisible(false);
    cross2->setVisible(false);

    // initialize variables
    isShip = false;
    isMiss = false;
    isHit = false;
    isCellForPlace = false;

    // include event
    setAcceptHoverEvents(true);
}

void Cell::drawCross(){

    // draw cross
    cross1->setVisible(true);
    cross2->setVisible(true);
}

void Cell::drawBlast1(){

    // draw blast 1
    addToGroup(blast1);
    blast1->setPixmap(QPixmap(QString(":/blast/Images/blast(1).png")));
    blast1->setPos(10,10);
}

void Cell::drawBlast2(){

    // remove blast 1
    removeFromGroup(blast1);
    delete blast1;

    // draw blast 2
    addToGroup(blast2);
    blast2->setPixmap(QPixmap(QString(":/blast/Images/blast(2).png")));
    blast2->setPos(-5,-5);

    // draw ship
    pixItem->setVisible(true);
}

void Cell::setPlaceMode(){

    // set isCellForPlace and delete useless variables
    isCellForPlace = true;
    delete cross1;
    delete cross2;
    delete blast1;
    delete blast2;
    delete pixItem;
}

void Cell::setImage(QGraphicsPixmapItem* pix){

    // set PixItem
    pixItem->setPixmap(pix->pixmap());
    pixItem->setPos(pix->pos());
    addToGroup(pixItem);
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if(game->shipToPlace && !isCellForPlace && game->placeMode){

        // place one ship
        game->placeSpecifiedShip(this);
    }
    else if(game->gameMode){

        // attack
        game->attack(this);
    }
}

void Cell::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(!isCellForPlace){
        // change color to yellow
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::yellow);
        square->setBrush(brush);
    }
}

void Cell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(!isCellForPlace){
        // back to default
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::transparent);
        square->setBrush(brush);
    }
}
