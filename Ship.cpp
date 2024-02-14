#include "Ship.h"
#include <QDebug>
#include "Game.h"


extern Game * game;

Ship::Ship(QGraphicsItem *parent){
    // initialize the variables
    numDeck = 0;
    horizontal = true;
    countHit = 0;
    nameShip = "Ship";
    owner = "NOONE";

    // create max num of cell
    cell1 = new Cell();
    cell2 = new Cell();
    cell3 = new Cell();
    cell4 = new Cell();

    pixItem1 = new QGraphicsPixmapItem();
    pixItem2 = new QGraphicsPixmapItem();
    pixItem3 = new QGraphicsPixmapItem();
    pixItem4 = new QGraphicsPixmapItem();
}

void Ship::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // if this ship NOT placed then pick it up
    if(game->placeMode){
        game->pickUpShip(this);
    }
}

void Ship::makeSkinShip(bool visiable){
    // set pixItem to all cells in this ship
    if(getHorizontal()){
        switch (getNumDeck()) {
        case 1:
            setPixmap(QPixmap(QString(":/Ships/Images/ship1.png")));
            pixItem1->setPixmap(QPixmap(QString(":/Ships/Images/ship1(1).png")));
            pixItem1->setPos(5,5);
            pixItem1->setVisible(visiable);
            cell1->setImage(pixItem1);
            cell1->isShip = true;
            break;
        case 2:
            setPixmap(QPixmap(QString(":/Ships/Images/ship2.png")));
            pixItem1->setPixmap(QPixmap(QString(":/Ships/Images/ship2(1).png")));
            pixItem1->setPos(10,4);
            pixItem1->setVisible(visiable);
            cell1->setImage(pixItem1);
            cell1->isShip = true;

            pixItem2->setPixmap(QPixmap(QString(":/Ships/Images/ship2(2).png")));
            pixItem2->setPos(0,4);
            pixItem2->setVisible(visiable);
            cell2->setImage(pixItem2);
            cell2->isShip = true;
            break;
        case 3:
            setPixmap(QPixmap(QString(":/Ships/Images/ship3.png")));
            pixItem1->setPixmap(QPixmap(QString(":/Ships/Images/ship3(1).png")));
            pixItem1->setPos(10,3);
            pixItem1->setVisible(visiable);
            cell1->setImage(pixItem1);
            cell1->isShip = true;

            pixItem2->setPixmap(QPixmap(QString(":/Ships/Images/ship3(2).png")));
            pixItem2->setPos(0,3);
            pixItem2->setVisible(visiable);
            cell2->setImage(pixItem2);
            cell2->isShip = true;

            pixItem3->setPixmap(QPixmap(QString(":/Ships/Images/ship3(3).png")));
            pixItem3->setPos(0,3);
            pixItem3->setVisible(visiable);
            cell3->setImage(pixItem3);
            cell3->isShip = true;
            break;
        case 4:
            setPixmap(QPixmap(QString(":/Ships/Images/ship4.png")));
            pixItem1->setPixmap(QPixmap(QString(":/Ships/Images/ship4(1).png")));
            pixItem1->setPos(10,2);
            pixItem1->setVisible(visiable);
            cell1->setImage(pixItem1);
            cell1->isShip = true;

            pixItem2->setPixmap(QPixmap(QString(":/Ships/Images/ship4(2).png")));
            pixItem2->setPos(0,2);
            pixItem2->setVisible(visiable);
            cell2->setImage(pixItem2);
            cell2->isShip = true;

            pixItem3->setPixmap(QPixmap(QString(":/Ships/Images/ship4(3).png")));
            pixItem3->setPos(0,2);
            pixItem3->setVisible(visiable);
            cell3->setImage(pixItem3);
            cell3->isShip = true;

            pixItem4->setPixmap(QPixmap(QString(":/Ships/Images/ship4(4).png")));
            pixItem4->setPos(0,2);
            pixItem4->setVisible(visiable);
            cell4->setImage(pixItem4);
            cell4->isShip = true;
            break;
        }
    }
    else if (!getHorizontal()){
        switch (getNumDeck()) {
        case 1:
            setPixmap(QPixmap(QString(":/Ships/Images/ship1v.png")));
            pixItem1->setPixmap(QPixmap(QString(":/Ships/Images/ship1(1)v.png")));
            pixItem1->setPos(5,5);
            pixItem1->setVisible(visiable);
            cell1->setImage(pixItem1);
            cell1->isShip = true;
            break;
        case 2:
            setPixmap(QPixmap(QString(":/Ships/Images/ship2v.png")));
            pixItem1->setPixmap(QPixmap(QString(":/Ships/Images/ship2(1)v.png")));
            pixItem1->setPos(4,10);
            pixItem1->setVisible(visiable);
            cell1->setImage(pixItem1);
            cell1->isShip = true;

            pixItem2->setPixmap(QPixmap(QString(":/Ships/Images/ship2(2)v.png")));
            pixItem2->setPos(4,0);
            pixItem2->setVisible(visiable);
            cell2->setImage(pixItem2);
            cell2->isShip = true;
            break;
        case 3:
            setPixmap(QPixmap(QString(":/Ships/Images/ship3v.png")));
            pixItem1->setPixmap(QPixmap(QString(":/Ships/Images/ship3(1)v.png")));
            pixItem1->setPos(3,10);
            pixItem1->setVisible(visiable);
            cell1->setImage(pixItem1);
            cell1->isShip = true;

            pixItem2->setPixmap(QPixmap(QString(":/Ships/Images/ship3(2)v.png")));
            pixItem2->setPos(3,0);
            pixItem2->setVisible(visiable);
            cell2->setImage(pixItem2);
            cell2->isShip = true;

            pixItem3->setPixmap(QPixmap(QString(":/Ships/Images/ship3(3)v.png")));
            pixItem3->setPos(3,0);
            pixItem3->setVisible(visiable);
            cell3->setImage(pixItem3);
            cell3->isShip = true;
            break;
        case 4:
            setPixmap(QPixmap(QString(":/Ships/Images/ship4v.png")));
            pixItem1->setPixmap(QPixmap(QString(":/Ships/Images/ship4(1)v.png")));
            pixItem1->setPos(2,10);
            pixItem1->setVisible(visiable);
            cell1->setImage(pixItem1);
            cell1->isShip = true;

            pixItem2->setPixmap(QPixmap(QString(":/Ships/Images/ship4(2)v.png")));
            pixItem2->setPos(2,0);
            pixItem2->setVisible(visiable);
            cell2->setImage(pixItem2);
            cell2->isShip = true;

            pixItem3->setPixmap(QPixmap(QString(":/Ships/Images/ship4(3)v.png")));
            pixItem3->setPos(2,0);
            pixItem3->setVisible(visiable);
            cell3->setImage(pixItem3);
            cell3->isShip = true;

            pixItem4->setPixmap(QPixmap(QString(":/Ships/Images/ship4(4)v.png")));
            pixItem4->setPos(2,0);
            pixItem4->setVisible(visiable);
            cell4->setImage(pixItem4);
            cell4->isShip = true;
            break;
        }
    }
}

void Ship::increaseCountHit(){
    countHit++;
}

void Ship::destroyShip(QString player){

    // decrease numShipsPlayers
    if(player == QString("PLAYER1")){
        game->numShipsPlayer2--;
    }
    else if(player == QString("PLAYER2")){
        game->numShipsPlayer1--;
    }

    // iterate over the ship coordinates and destoy them
    for(int i = 0; i < coorXY.size(); i++){
        int x = coorXY[i].first;
        int y = coorXY[i].second;

        // show blast2 and ship
        if(player == QString("PLAYER1")){
            game->player2Map[x][y]->drawBlast2();
        }
        else if(player == QString("PLAYER2")){
            game->player1Map[x][y]->drawBlast2();
        }

        // iterates over the coordinates around the ship and make them Miss
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if(player == QString("PLAYER1")){
                    if (game->isCellInMap(x + dx, y + dy) && !game->player2Map[x + dx][y + dy]->isMiss && !game->player2Map[x + dx][y + dy]->isHit) {
                        game->player2Map[x + dx][y + dy]->isMiss = true;
                        game->player2Map[x + dx][y + dy]->drawCross();
                    }
                }
                else if(player == QString("PLAYER2")){
                    if (game->isCellInMap(x + dx, y + dy) && !game->player1Map[x + dx][y + dy]->isMiss && !game->player1Map[x + dx][y + dy]->isHit) {
                        game->player1Map[x + dx][y + dy]->isMiss = true;
                        game->player1Map[x + dx][y + dy]->drawCross();
                    }
                }
            }
        }
    }
}

int Ship::getNumDeck(){
    return numDeck;
}

bool Ship::getHorizontal(){
    return horizontal;
}

int Ship::getCountHit(){
    return countHit;
}

QString Ship::getNameShip(){
    return nameShip;
}

QString Ship::getOwner(){
    return owner;
}

void Ship::setNumDeck(int number){
    numDeck = number;
}

void Ship::setNameShip(QString name){
    nameShip = name;
}

void Ship::setHorizontal(bool hor){
    horizontal = hor;
}

void Ship::setOwner(QString player){
    owner = player;
}
