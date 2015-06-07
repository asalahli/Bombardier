#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include "Screen.hpp"
#include <list>

class Missile;
class PlayerShip;
class StatusBar;
class NumberLabel;
class Cursor;
class BasicEnemy;
class Explosion;
class InfoBox;
class InfoBox2;

class GameplayScreen : public Screen {
    PlayerShip* mPlayer;
    StatusBar* mStatusBar;
    NumberLabel* mScore;
    InfoBox* mInfoBox;
    InfoBox2* mInfoBox2;

    std::list<Missile*> mMissiles;
    std::list<BasicEnemy*> mEnemies;
    std::list<Explosion*> mExplosions;

    Cursor* mCursor;

    bool mGamePaused;
    float mSpawnCooldown;
public:
    GameplayScreen(Game& game);
    ~GameplayScreen();

    virtual void onMouseDown(sf::Vector2f& pos, sf::Mouse::Button button);
    virtual void onMouseMove(sf::Vector2f& pos);

    virtual void onKeyDown(sf::Keyboard::Key key);

    void toggleGamePaused();
    void spawnBasicEnemy();

    void update(float dt);
    void draw();
};

#endif // GAMEPLAY_SCREEN_H
