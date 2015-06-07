#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameObject.hpp"

class Explosion : public GameObject {
    int mFrame;
    float mElapsed;

    bool mLast;

    GameObject* mDeadObj;

    sf::Sound mSFX;
public:
    Explosion(Screen& screen, GameObject* deadObj, float x, float y, bool last=false);
    ~Explosion();

    void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawDeadObject(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // EXPLOSION_H

