#include "mine.h"
#include "Game.h"

extern Game * game;

mine::mine(): Ship(){

    // set difault size and name
    setNumDeck(1);
    setNameShip(QString("mine"));
}

void mine::makeSkinShip(bool visiable){

    // set pixItem to cell in this mine
    setPixmap(QPixmap(QString(":/mine/Images/mine.png")));
    pixItem1->setPixmap(QPixmap(QString(":/mine/Images/mine.png")));
    pixItem1->setPos(5,5);
    pixItem1->setVisible(visiable);
    cell1->setImage(pixItem1);
    cell1->isShip = true;
}

void mine::destroyShip(QString player){

    // decrease numMinePlayers
    if(player == QString("PLAYER1")){
        game->numMinePlayer2--;
    }
    else if(player == QString("PLAYER2")){
        game->numMinePlayer1--;
    }

    // iterat over the ship coordinates and destoy them
    for(int i = 0; i < coorXY.size(); i++){
        int x = coorXY[i].first;
        int y = coorXY[i].second;
        if(player == QString("PLAYER1")){
            game->player2Map[x][y]->drawBlast2();
        }
        else if(player == QString("PLAYER2")){
            game->player1Map[x][y]->drawBlast2();
        }

        // make Hit or Miss to enemy map in specified coord
        if(player == QString("PLAYER1")){
            if (game->isCellInMap(x, y) && !game->player1Map[x][y]->isMiss && !game->player1Map[x][y]->isHit){
                if(game->player1Map[x][y]->isShip){
                    game->player1Map[x][y]->isHit = true;
                    game->player1Map[x][y]->drawBlast1();
                    game->setWhosTurn(QString("PLAYER2"));
                    game->checkShipInHit(game->player1Map[x][y]);
                    game->setWhosTurn(QString("PLAYER1"));

                }
                else{
                    game->player1Map[x][y]->isMiss = true;
                    game->player1Map[x][y]->drawCross();
                }
            }
        }
        else if(player == QString("PLAYER2")){
            if (game->isCellInMap(x, y) && !game->player2Map[x][y]->isMiss && !game->player2Map[x][y]->isHit){
                if(game->player2Map[x][y]->isShip){
                    game->player2Map[x][y]->isHit = true;
                    game->player2Map[x][y]->drawBlast1();
                    game->setWhosTurn(QString("PLAYER1"));
                    game->checkShipInHit(game->player2Map[x][y]);
                    game->setWhosTurn(QString("PLAYER2"));

                    if(game->botMode && game->getWhosTurn() == QString("PLAYER2")){
                        game->hitedCell.push_back(QPair<Cell*, int>(game->player2Map[x][y], 2));
                    }
                }
                else{
                    game->player2Map[x][y]->isMiss = true;
                    game->player2Map[x][y]->drawCross();
                }
            }
        }
    }
}
