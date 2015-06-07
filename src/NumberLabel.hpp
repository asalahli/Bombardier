#ifndef NUMBER_LABEL_H
#define NUMBER_LABEL_H

#include "GameObject.hpp"

class NumberLabel : public GameObject {
    int n;
public:
    NumberLabel(Screen& screen);

    int getNumber() { return n; }
    void setNumber(int number);
};

#endif // NUMBER_LABEL_H

