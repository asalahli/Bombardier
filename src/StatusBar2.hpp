#ifndef STATUS_BAR2_H
#define STATUS_BAR2_H

#include "GameObject.hpp"

class StatusBar2 : public GameObject {
    int mHealth;
public:
    StatusBar2(Screen& screen);

    int getHealth() { return mHealth; };
    void setHealth(int health);
};

#endif // STATUS_BAR2_H
