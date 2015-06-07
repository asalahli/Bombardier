#ifndef MISSILE_H
#define MISSILE_H

#include "GameObject.hpp"

class Missile : public GameObject {
public:
    Missile(Screen& screen, GameObject* o, bool enemy=true);

    GameObject* owner;
    int damage;

    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // MISSILE_H
