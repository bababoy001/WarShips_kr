#ifndef BOTLVL2_H
#define BOTLVL2_H

#include "Bot.h"
#include <QPair>

class BotLvl2 : public Bot {
public:
    // constructor
    BotLvl2();

    // public methods
    void botAttack() override;
    void takeCoord(int &x, int &y) override;
    void findNextTarget(int& x, int& y);
    void reverseDirection();

private:
    // private variables
    QPair<int, int> firstHit;
    QPair<int, int> lastHit;
    bool destroying;
    int directionIndex;
    bool foundDirection;
    int attempt;
    int lastPlayerShips;
    int lastPlayerMine;
};

#endif // BOTLVL2_H
