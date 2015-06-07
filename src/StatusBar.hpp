#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include "GameObject.hpp"

class StatusBar : public GameObject {
    int mHealth;
public:
    StatusBar(Screen& screen);

    int getHealth() { return mHealth; };
    void setHealth(int health);
};

#endif // STATUS_BAR_H
