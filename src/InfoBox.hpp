#ifndef INFO_BOX_H
#define INFO_BOX_H

#include "GameObject.hpp"

#define CORNER 20

class InfoBox : public GameObject {
    sf::RectangleShape bg;
    sf::Sprite lmb;
    sf::Sprite rmb;
    sf::Text help1;
    sf::Text help2;
    sf::Text help3;
public:
    InfoBox(Screen& screen);

    void setBoxCoords(sf::FloatRect box);

    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // INFO_BOX_H

