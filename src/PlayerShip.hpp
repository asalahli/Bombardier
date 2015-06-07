#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "GameObject.hpp"

class Missile;

class PlayerShip : public GameObject {
    float mCycle, mElapsed;
    bool mIsFirst;

    sf::Vector2f mDestination;
    float mDistanceLeft;
    bool mIsMoving;

    sf::Sound mSFX;

    float mCooldown;

    int mHealth;
public:
    PlayerShip(Screen& screen);

    void pointTo(sf::Vector2f point);
    void moveTo(sf::Vector2f point);
    void fire(std::list<Missile*>& missiles);
    int getHealth() { return mHealth; };
    void setHealth(int health);

    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // PLAYER_SHIP_H
