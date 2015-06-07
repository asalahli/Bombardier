#include "GameplayScreen.hpp"
#include "PlayerShip.hpp"
#include "StatusBar.hpp"
#include "Missile.hpp"
#include "Cursor.hpp"
#include "NumberLabel.hpp"
#include "BasicEnemy.hpp"
#include "Collision.hpp"
#include "Explosion.hpp"
#include "InfoBox.hpp"
#include "InfoBox2.hpp"

#define SPAWN_RATE 1.0f
#define MAX_ENEMY_COUNT 4

class Box : public GameObject {
public:
    Box(Screen& screen)
    : GameObject(screen)
    {
        boundingPolygon.push_back(sf::Vector2f(0, 100));
        boundingPolygon.push_back(sf::Vector2f(100, 0));
        boundingPolygon.push_back(sf::Vector2f(0, -100));
        boundingPolygon.push_back(sf::Vector2f(-100, 0));
    }
};

GameplayScreen::GameplayScreen(Game& game)
    : Screen(game)
    , mSpawnCooldown(SPAWN_RATE)
{
    mPlayer = new PlayerShip(*this);
    mPlayer->setHealth(100);
    mCursor = new Cursor(*this);

    mStatusBar = new StatusBar(*this);
    mStatusBar->setScale(2, 2);
    mStatusBar->setPosition(-350, -250);
    mStatusBar->setHealth(100);

    mScore = new NumberLabel(*this);
    mScore->setScale(2, 2);
    mScore->setPosition(1100, -250);

    mInfoBox = new InfoBox(*this);
    mInfoBox2 = new InfoBox2(*this);

    spawnBasicEnemy();

    mGamePaused = true;
}

GameplayScreen::~GameplayScreen() {
    for (Missile* missile : mMissiles) {
        delete missile;
    }

    delete mCursor;
    delete mStatusBar;
    delete mPlayer;
    delete mScore;
    delete mInfoBox;
}

void GameplayScreen::update(float dt) {
    if (mPaused) return;
    if (mGamePaused) return;

    for (Missile* missile : mMissiles) {
        if (missile->owner != mPlayer) {
            if (mPlayer && !mPlayer->isDead) {
                sf::Vector2f collision = 1.1f * checkCollision(mPlayer, missile);
                if (collision.x != 0 || collision.y != 0) {
                    mPlayer->setHealth(mPlayer->getHealth() - missile->damage);
                    mStatusBar->setHealth(mPlayer->getHealth());
                    missile->isDead = true;
                    if (mPlayer->getHealth() <= 0) {
                        mPlayer->isDead = true;
                    }
                    continue;
                }
            }
        }
        else {
            for (BasicEnemy* enemy : mEnemies) {
                if (!enemy->isDead) {
                    sf::Vector2f collision = 1.1f * checkCollision(enemy, missile);
                    if (collision.x != 0 || collision.y != 0) {
                        enemy->setHealth(enemy->getHealth() - missile->damage);
                        missile->isDead = true;
                        if (enemy->getHealth() <= 0) {
                            enemy->isDead = true;
                            mScore->setNumber(mScore->getNumber()+1);
                        }
                        break;
                    }
                }
            }
        }
    }

    if (mPlayer && !mPlayer->isDead) {
        mPlayer->update(dt);
    }
    mStatusBar->update(dt);
    mScore->update(dt);

    int w = getGame().getWindow().getSize().x;
    int h = getGame().getWindow().getSize().y;

    sf::IntRect innerRect(0, 0, w, h);

    sf::Vector2i sizei(w, h);
    sf::Vector2f sizef = getGame().getWindow().mapPixelToCoords(sizei);

    w = round(sizef.x);
    h = round(sizef.y);

    sizef = getGame().getWindow().mapPixelToCoords(sf::Vector2i(0, 0));
    int l = round(sizef.x);
    int t = round(sizef.y);

    sf::IntRect outerRect(l-50, t-50, abs(l)+abs(w)+50, abs(t)+abs(h)+50);

    if (mPlayer && mPlayer->isDead) {
        mExplosions.push_back(new Explosion(*this, mPlayer, mPlayer->getPosition().x, mPlayer->getPosition().y, true));
        mPlayer = NULL;
    }

    for (std::list<Explosion*>::iterator i = mExplosions.begin(); i != mExplosions.end(); ) {
        if ((*i)->isDead) {
            delete (*i);
            i = mExplosions.erase(i);
        }
        else {
            (*i)->update(dt);
            i++;
        }
    }

    if (!mPlayer || mPlayer->isDead) return;

    if (mSpawnCooldown > 0)
        mSpawnCooldown -= dt;

    if (mSpawnCooldown < 0 && mEnemies.size() < MAX_ENEMY_COUNT) {
        spawnBasicEnemy();
        mSpawnCooldown = SPAWN_RATE;
    }

    for (std::list<BasicEnemy*>::iterator i = mEnemies.begin(); i != mEnemies.end(); ) {
        if ((*i)->isDead) {
            mExplosions.push_back(new Explosion(*this, *i, (*i)->getPosition().x, (*i)->getPosition().y));
            i = mEnemies.erase(i);
        }
        else {
            (*i)->update(dt);
            i++;
        }
    }

    for (std::list<Missile*>::iterator i = mMissiles.begin(); i != mMissiles.end(); ) {
        int x = round((*i)->getPosition().x);
        int y = round((*i)->getPosition().y);
        if (!outerRect.contains(x, y) || (*i)->isDead) {
            delete (*i);
            i = mMissiles.erase(i);
        }
        else {
            (*i)->update(dt);
            i++;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mPlayer) {
        if (innerRect.contains(sf::Mouse::getPosition(getGame().getWindow()))) {
            mPlayer->fire(mMissiles);
        }
    }

    for (BasicEnemy* enemy : mEnemies) {
        enemy->fire(mMissiles);
    }

//    sf::Vector2i pos = sf::Mouse::getPosition(getGame().getWindow());
//    sf::Vector2f coords = getGame().getWindow().mapPixelToCoords(pos);
//    mCursor->setPosition(coords);
}

void GameplayScreen::draw() {
    if (mPaused) return;
//    Box b1(*this);
//    Box b2(*this);
//
//    b1.setRotation(45);
//    b2.setPosition(125, 125);
//
//    sf::Vector2f collision = checkCollision(&b1, &b2);
//    std::cerr << collision.x << " " << collision.y << std::endl;
//
//    getGame().getWindow().draw(b1);
//    getGame().getWindow().draw(b2);
//
//    return;

    sf::Texture* bgtexture = getGame().getResourceManager().getTexture("bg.png");
    bgtexture->setRepeated(true);
    sf::Sprite bgsprite(*bgtexture);
    bgsprite.setPosition(getGame().getWindow().mapPixelToCoords(sf::Vector2i(0, 0)));
    bgsprite.setTextureRect(sf::IntRect(0, 0, getGame().getWindow().getSize().x*2, getGame().getWindow().getSize().y*2));
    getGame().getWindow().draw(bgsprite);

    sf::RenderStates states = sf::RenderStates::Default;
    states.texture = getGame().getResourceManager().getTexture("space.png");

    if (mPlayer) {
        getGame().getWindow().draw(*mPlayer, states);
    }

    for (Missile* missile : mMissiles) {
        getGame().getWindow().draw(*missile, states);
    }

    for (BasicEnemy* enemy : mEnemies) {
        getGame().getWindow().draw(*enemy, states);
    }

    for (Explosion* explosion : mExplosions) {
        explosion->drawDeadObject(getGame().getWindow(), states);
    }

    getGame().getWindow().draw(*mScore, states);
    states.texture = getGame().getResourceManager().getTexture("ui.png");
    getGame().getWindow().draw(*mStatusBar, states);

    for (BasicEnemy* enemy : mEnemies) {
        enemy->drawHealthBar(getGame().getWindow(), states);
    }

    states.texture = getGame().getResourceManager().getTexture("explosion.png");
    for (Explosion* explosion : mExplosions) {
        getGame().getWindow().draw(*explosion, states);
    }

    if (getGame().isGameOver()) {
        states.texture = getGame().getResourceManager().getTexture("ui.png");
        getGame().getWindow().draw(*mInfoBox2, states);
    }
    else if (mGamePaused) {
        states.texture = getGame().getResourceManager().getTexture("ui.png");
        getGame().getWindow().draw(*mInfoBox, states);
    }
}

void GameplayScreen::onMouseDown(sf::Vector2f& pos, sf::Mouse::Button button) {
    if (mPaused) return;

    if (button == sf::Mouse::Left) {
    }
    else if (button == sf::Mouse::Right) {
        if (mPlayer) {
            mPlayer->moveTo(pos);
        }
    }
}

void GameplayScreen::onMouseMove(sf::Vector2f& pos) {
    if (mPaused) return;
    if (mGamePaused) return;

    if (mPlayer) {
        mPlayer->pointTo(pos);
    }
}

void GameplayScreen::onKeyDown(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Space)
        toggleGamePaused();
}

void GameplayScreen::toggleGamePaused() {
    mGamePaused = !mGamePaused;
}

void GameplayScreen::spawnBasicEnemy() {
    BasicEnemy* enemy = new BasicEnemy(*this);

//    enemy->setVelocity(-50, -50);
    enemy->setPosition(rand() % 800, rand() % 600);
    enemy->setRotation(rand() % 360);
    enemy->setHealth(100);
    enemy->mPlayerShip = mPlayer;

    mEnemies.push_back(enemy);
}
