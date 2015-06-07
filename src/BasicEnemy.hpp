#ifndef BASIC_ENEMY_H
#define BASIC_ENEMY_H

#include "GameObject.hpp"
#include "StatusBar2.hpp"

class Missile;

class BasicEnemy : public GameObject {
    int mHealth;

    sf::Sound mSFX;

    float mCooldown;

    bool mCanSee;
    float mAngularVelocity;

    StatusBar2* mHealthBar;
public:
    BasicEnemy(Screen& screen);
    ~BasicEnemy() { delete mHealthBar; };

    GameObject* mPlayerShip;

    void fire(std::list<Missile*>& missiles);
    void setHealth(int health) { mHealth = health; mHealthBar->setHealth(health); };
    int getHealth() { return mHealth; };

    virtual void update(float dt);
    virtual void drawHealthBar(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // BASIC_ENEMY_H

