#ifndef MINE_H
#define MINE_H

#include "Ship.h"

class mine:public Ship{
public:
    // constructors
    mine();

    // public methods
    void makeSkinShip(bool visiable) override;
    void destroyShip(QString player) override;
};

#endif // MINE_H
