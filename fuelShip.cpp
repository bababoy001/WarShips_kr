#include "fuelShip.h"
#include "Game.h"
#include <QPair>

extern Game * game;

fuelShip::fuelShip(): Ship(){

    // set difault size and name
    setNumDeck(4);
    setNameShip(QString("fuelShip"));
}

void fuelShip::makeSkinShip(bool visiable){
    // set pixItem to all cells in this ship
    if(getHorizontal()){
        setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShip.png")));
        pixItem1->setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShip(1).png")));
        pixItem1->setPos(10,2);
        pixItem1->setVisible(visiable);
        cell1->setImage(pixItem1);
        cell1->isShip = true;

        pixItem2->setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShip(2).png")));
        pixItem2->setPos(0,2);
        pixItem2->setVisible(visiable);
        cell2->setImage(pixItem2);
        cell2->isShip = true;

        pixItem3->setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShip(3).png")));
        pixItem3->setPos(0,2);
        pixItem3->setVisible(visiable);
        cell3->setImage(pixItem3);
        cell3->isShip = true;

        pixItem4->setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShip(4).png")));
        pixItem4->setPos(0,2);
        pixItem4->setVisible(visiable);
        cell4->setImage(pixItem4);
        cell4->isShip = true;
    }
    else if (!getHorizontal()){
        setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShipv.png")));
        pixItem1->setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShip(1)v.png")));
        pixItem1->setPos(2,10);
        pixItem1->setVisible(visiable);
        cell1->setImage(pixItem1);
        cell1->isShip = true;

        pixItem2->setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShip(2)v.png")));
        pixItem2->setPos(2,0);
        pixItem2->setVisible(visiable);
        cell2->setImage(pixItem2);
        cell2->isShip = true;

        pixItem3->setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShip(3)v.png")));
        pixItem3->setPos(2,0);
        pixItem3->setVisible(visiable);
        cell3->setImage(pixItem3);
        cell3->isShip = true;

        pixItem4->setPixmap(QPixmap(QString(":/fuelShip/Images/fuelShip(4)v.png")));
        pixItem4->setPos(2,0);
        pixItem4->setVisible(visiable);
        cell4->setImage(pixItem4);
        cell4->isShip = true;
    }
}

void fuelShip::destroyShip(QString player){

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

        // iterates over the coordinates around the ship and make them Miss or Hit if it's ship
        for (int dx = -2; dx <= 2; dx++) {
            for (int dy = -2; dy <= 2; dy++) {
                if(player == QString("PLAYER1")){
                    if (game->isCellInMap(x + dx, y + dy) && !game->player2Map[x + dx][y + dy]->isMiss && !game->player2Map[x + dx][y + dy]->isHit) {
                        if(game->player2Map[x + dx][y + dy]->isShip){
                            game->player2Map[x + dx][y + dy]->isHit = true;
                            game->player2Map[x + dx][y + dy]->drawBlast1();
                            game->checkShipInHit(game->player2Map[x + dx][y + dy]);
                            if(game->botMode && game->getWhosTurn() == QString("PLAYER1")){
                                game->hitedCell.push_back(QPair<Cell*, int>(game->player2Map[x + dx][y + dy], 2));
                            }
                        }
                        else{
                            game->player2Map[x + dx][y + dy]->isMiss = true;
                            game->player2Map[x + dx][y + dy]->drawCross();
                        }
                    }
                }
                else if(player == QString("PLAYER2")){
                    if (game->isCellInMap(x + dx, y + dy) && !game->player1Map[x + dx][y + dy]->isMiss && !game->player1Map[x + dx][y + dy]->isHit) {
                        if(game->player1Map[x + dx][y + dy]->isShip){
                            game->player1Map[x + dx][y + dy]->isHit = true;
                            game->player1Map[x + dx][y + dy]->drawBlast1();
                            game->checkShipInHit(game->player1Map[x + dx][y + dy]);
                        }
                        else{
                            game->player1Map[x + dx][y + dy]->isMiss = true;
                            game->player1Map[x + dx][y + dy]->drawCross();
                        }
                    }
                }
            }
        }
    }
}
