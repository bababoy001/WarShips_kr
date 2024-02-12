#include "Bot.h"
#include "Game.h"

extern Game * game;

Bot::Bot(){}

void Bot::botAttack(){
    // initialize X and Y
    int x, y;

    // get random coord
    takeCoord(x, y);

    // attack this coord
    game->attack(game->player2Map[x][y]);
}

void Bot::takeCoord(int &x, int &y){
    // set random coord
    x = rand() % game->getWidthMap();
    y = rand() % game->getHeightMap();
}
