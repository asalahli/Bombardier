#include "NumberLabel.hpp"

NumberLabel::NumberLabel(Screen& screen)
    : GameObject(screen)
{
    setNumber(0);
}

void NumberLabel::setNumber(int number) {
    if (number < 0) number = 0;

    n = number;

    if (n == 0) {
        mVertices.resize(4);
        getScreen().getGame().getResourceManager().loadSprite(this, 0, "numeral0.png", 0, 0);
    }
    else {
        int count = 0;
        for (int m=n; m!=0; count++, m/= 10);

        std::string sprite = "numeral0.png";

        mVertices.resize(count*4);
        for (int m=n, i=0; i<count; i++, m/=10) {
            sprite[7] = (m%10) + 48;
            getScreen().getGame().getResourceManager().loadSprite(
                this, i, sprite, -i*19, 0);
        }
    }
}
