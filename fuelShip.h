#ifndef FUELSHIP_H
#define FUELSHIP_H

#include "Ship.h"

class fuelShip:public Ship{
public:
    // constructors
    fuelShip();

    // public methods
    void makeSkinShip(bool visiable) override;
    void destroyShip(QString player) override;
};

#endif // FUELSHIP_H
