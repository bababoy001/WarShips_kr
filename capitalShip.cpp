#include "capitalShip.h"
#include "Game.h"

extern Game * game;

capitalShip::capitalShip(): Ship(){

    // set difault size and name
    setNumDeck(4);
    setNameShip(QString("capitalShip"));
}

void capitalShip::makeSkinShip(bool visiable){
    // set pixItem to all cells in this ship
    if(getHorizontal()){
        setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShip.png")));
        pixItem1->setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShip(1).png")));
        pixItem1->setPos(10,2);
        pixItem1->setVisible(visiable);
        cell1->setImage(pixItem1);
        cell1->isShip = true;

        pixItem2->setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShip(2).png")));
        pixItem2->setPos(0,2);
        pixItem2->setVisible(visiable);
        cell2->setImage(pixItem2);
        cell2->isShip = true;

        pixItem3->setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShip(3).png")));
        pixItem3->setPos(0,2);
        pixItem3->setVisible(visiable);
        cell3->setImage(pixItem3);
        cell3->isShip = true;

        pixItem4->setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShip(4).png")));
        pixItem4->setPos(0,2);
        pixItem4->setVisible(visiable);
        cell4->setImage(pixItem4);
        cell4->isShip = true;
    }
    else if (!getHorizontal()){
        setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShipv.png")));
        pixItem1->setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShip(1)v.png")));
        pixItem1->setPos(2,10);
        pixItem1->setVisible(visiable);
        cell1->setImage(pixItem1);
        cell1->isShip = true;

        pixItem2->setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShip(2)v.png")));
        pixItem2->setPos(2,0);
        pixItem2->setVisible(visiable);
        cell2->setImage(pixItem2);
        cell2->isShip = true;

        pixItem3->setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShip(3)v.png")));
        pixItem3->setPos(2,0);
        pixItem3->setVisible(visiable);
        cell3->setImage(pixItem3);
        cell3->isShip = true;

        pixItem4->setPixmap(QPixmap(QString(":/capitalShip/Images/capitalShip(4)v.png")));
        pixItem4->setPos(2,0);
        pixItem4->setVisible(visiable);
        cell4->setImage(pixItem4);
        cell4->isShip = true;
    }
}

void capitalShip::destroyShip(QString player){

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

        // show blast2 and ship, and set zalp mode
        if(player == QString("PLAYER1")){
            game->player2Map[x][y]->drawBlast2();
            game->zalpMode1 = 0;
            game->zalpMode2 = 2;
        }
        else if(player == QString("PLAYER2")){
            game->player1Map[x][y]->drawBlast2();
            game->zalpMode2 = 0;
            game->zalpMode1 = 2;
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
