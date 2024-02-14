#include "BotLvl2.h"
#include "Game.h"

extern Game * game;

BotLvl2::BotLvl2(){
    // initialize variables
    firstHit = QPair<int, int>(-1, -1);
    lastHit = QPair<int, int>(-1, -1);
    destroying = false;
    directionIndex = 0;
    foundDirection = false;
    attempt = 0;
    lastPlayerShips = 0;
    lastPlayerMine = 0;
}

void BotLvl2::botAttack(){
    // initialize X and Y
    int x, y;

    // check the number of ships
    if (game->numShipsPlayer2 < lastPlayerShips) {
        attempt = 0;
        destroying = false;
        foundDirection = false;
    }

    // check the number of mines
    if (game->numMinePlayer2 < lastPlayerMine) {
        attempt = 0;
        destroying = false;
        foundDirection = false;
    }

    // set new number of ships and mines
    lastPlayerShips = game->numShipsPlayer2;
    lastPlayerMine = game->numMinePlayer2;

    // take new coord
    takeCoord(x, y);

    if (game->player2Map[x][y]->isShip && !game->player2Map[x][y]->isHit) {
        if (!destroying) {

            // save coord if bot hit ship first time
            firstHit = QPair<int, int>(x, y);
            lastHit = QPair<int, int>(x, y);

            // set destroying mode
            destroying = true;
        }
    }

    // attack coord
    game->attack(game->player2Map[x][y]);
}

void BotLvl2::takeCoord(int &x, int &y){
    if (!destroying) {
        // get random coord
        x = rand() % game->getWidthMap();
        y = rand() % game->getHeightMap();
    }
    else {
        // find new coord after hit ship
        findNextTarget(x, y);
    }
}

void BotLvl2::findNextTarget(int &x, int &y){
    // if (attempt >= 4) { // TODO delete
    //     x = -1;
    //     y = -1;
    //     return;
    // }

    // initialize all directions
    QVector<QPair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    // try to find direction
    int dx = directions[directionIndex].first;
    int dy = directions[directionIndex].second;

    // new coord
    int newX = lastHit.first + dx;
    int newY = lastHit.second + dy;

    // if coord out of map
    if (!game->isCellInMap(newX, newY)) {

        // change side if you know direction
        if (foundDirection) {
            lastHit = firstHit;
            reverseDirection();
        }
        // try new direction if you don't know direction
        else {
            directionIndex = (directionIndex + 1) % 4;
            attempt++;
        }
        return findNextTarget(x, y);
    }

    // if bot miss
    if (game->isCellInMap(newX, newY) && !game->player2Map[newX][newY]->isHit && !game->player2Map[newX][newY]->isMiss && !game->player2Map[newX][newY]->isShip) {

        // if you know direction - miss and change side
        if (foundDirection) {
            x = newX;
            y = newY;
            lastHit = firstHit;
            reverseDirection();
        }
        // if you don't know direction - miss and try new direction
        else {
            directionIndex = (directionIndex + 1) % 4;
            attempt++;
            x = newX;
            y = newY;
            return;
        }
    }
    // if this cell already miss - try new direction
    else if (game->isCellInMap(newX, newY) && game->player2Map[newX][newY]->isMiss) {

        // change direction
        lastHit = firstHit;
        if (foundDirection) {
            reverseDirection();
            findNextTarget(x, y);
        }
        else {
            directionIndex = (directionIndex + 1) % 4;
            attempt++;
            findNextTarget(x, y);
        }
    }
    // if this cell is ship - hit ship
    else if (!game->player2Map[newX][newY]->isHit && game->player2Map[newX][newY]->isShip) {

        // new coord
        x = newX;
        y = newY;

        // save coord to last hit
        lastHit = QPair<int, int>(x, y);

        // save direction
        foundDirection = true;
    }
    // if this cell is hit - skip this cell
    else if (game->player2Map[newX][newY]->isShip) {
        lastHit = QPair<int, int>(newX, newY);
        foundDirection = true;
        findNextTarget(x, y);
    }
    // else try new direction
    else {
        directionIndex = (directionIndex + 1) % 4;
        attempt++;
        findNextTarget(x, y);
    }
}

void BotLvl2::reverseDirection(){

    // change side of direction to the opposite
    if (directionIndex == 0) directionIndex = 1;
    else if (directionIndex == 1) directionIndex = 0;
    else if (directionIndex == 2) directionIndex = 3;
    else if (directionIndex == 3) directionIndex = 2;
}
