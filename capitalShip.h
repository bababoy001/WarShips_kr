#ifndef CAPITALSHIP_H
#define CAPITALSHIP_H

#include "Ship.h"

class capitalShip:public Ship{
public:
    // constructors
    capitalShip();

    // public methods
    void makeSkinShip(bool visiable) override;
    void destroyShip(QString player) override;
};

#endif // CAPITALSHIP_H
