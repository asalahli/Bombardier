#ifndef INFO_BOX2_H
#define INFO_BOX2_H

#include "GameObject.hpp"

#define CORNER 20

class InfoBox2 : public GameObject {
    sf::RectangleShape bg;
    sf::Text help1;
    sf::Text help2;
public:
    InfoBox2(Screen& screen);

    void setBoxCoords(sf::FloatRect box);

    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif // INFO_BOX2_H

