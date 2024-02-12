#ifndef BOT_H
#define BOT_H

class Bot{
public:
    // constructor
    Bot();

    // public methods
    virtual void botAttack();
    virtual void takeCoord(int &x, int &y);
};

#endif // BOT_H
