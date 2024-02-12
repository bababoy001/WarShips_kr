#include "Game.h"


Game::Game(QWidget *parent)
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widthWindow = 1000;
    heightWindow = 800;

    // set up the scene
    scene = new QGraphicsScene();
    setScene(scene);

    // set up the screen and scene
    setWindowSize(widthWindow,heightWindow);

}



QString Game::getWhosTurn(){
    return whosTurn_;
}

int Game::getWidthMap(){
    return widthMap;
}

int Game::getHeightMap(){
    return heightMap;
}

void Game::setWindowSize(int width, int height){
    // set window width and height
    widthWindow = width;
    heightWindow = height;

    // set size of screen
    setFixedSize(width, height);

    // set size of scene
    scene->setSceneRect(0,0,width, height);
}

void Game::setMapSize(int rows, int columns){
    // resize map
    widthMap = rows;
    heightMap = columns;
}

void Game::setWhosTurn(QString player){
    // change the QString
    whosTurn_ = player;

    // change the color of players
    if(player == QString("PLAYER1")){
        // set textPlayer1 green, what meen his turn
        textPlayer1->setDefaultTextColor(QColor(Qt::green));

        // set textPlayer2 black
        textPlayer2->setDefaultTextColor(QColor(Qt::black));
    }
    else if(player == QString("PLAYER2")){
        // set textPlayer2 green, what meen his turn
        textPlayer2->setDefaultTextColor(QColor(Qt::green));

        // set textPlayer1 black
        textPlayer1->setDefaultTextColor(QColor(Qt::black));
    }
}
