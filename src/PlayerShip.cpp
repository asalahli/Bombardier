#include "PlayerShip.hpp"
#include "Missile.hpp"
#include "ResourceManager.hpp"
//#include <cmath>

// Points per second
#define SPEED 400

// Canon cooldown in seconds
#define COOLDOWN 0.1

PlayerShip::PlayerShip(Screen& screen)
    : GameObject(screen)
    , mCooldown(COOLDOWN)
{
    mVertices.resize(16);

    getScreen().getGame().getResourceManager().loadSprite(this, 0, "fire14.png", 18, 58);
    getScreen().getGame().getResourceManager().loadSprite(this, 1, "fire14.png", 67, 58);
    getScreen().getGame().getResourceManager().loadSprite(this, 2, "playerShip1_blue.png", 0, 0);

    mSFX.setBuffer(getScreen().getGame().getSoundBuffer());
    mSFX.setVolume(SFX_VOLUME);

    setOrigin(49, 40);
    setRotation(0);
    setPosition(200, 200);

    mElapsed = 0;
    mCycle = 0.025;
    mIsFirst = true;

    mIsMoving = false;
    mDestination = sf::Vector2f(0, 0);
    mDistanceLeft = 0;

    boundingPolygon.push_back(sf::Vector2f(49,  5));
    boundingPolygon.push_back(sf::Vector2f( 3, 51));
    boundingPolygon.push_back(sf::Vector2f(49, 74));
    boundingPolygon.push_back(sf::Vector2f(95, 51));
}

void PlayerShip::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    GameObject::draw(target, states);
}

void PlayerShip::update(float dt) {
    if (mIsMoving) {
        mDistanceLeft -= SPEED * dt;
        if (mDistanceLeft <= 0) {
            mDistanceLeft = 0;
            mIsMoving = false;
            setPosition(mDestination);
        }
        else {
            GameObject::update(dt);
        }
    }

    mElapsed += dt;
    if (mElapsed > mCycle) {
        mElapsed -= mCycle;
        mIsFirst = !mIsFirst;

        if (mIsFirst) {
            getScreen().getGame().getResourceManager().loadSprite(this, 0, "fire14.png", 18, 58);
            getScreen().getGame().getResourceManager().loadSprite(this, 1, "fire14.png", 67, 58);
        }
        else {
            getScreen().getGame().getResourceManager().loadSprite(this, 0, "fire15.png", 18, 58);
            getScreen().getGame().getResourceManager().loadSprite(this, 1, "fire15.png", 67, 58);
        }
    }

    if (mCooldown > 0)
        mCooldown -= dt;
    if (mCooldown < 0)
        mCooldown = 0;
}

void PlayerShip::pointTo(sf::Vector2f point) {
    sf::Vector2f coord = getPosition();

    if (coord.x == point.x && coord.y == point.y) {
        return;
    }

    if (coord.x == point.x) {
        if (coord.y > point.y) {
            setRotation(0);
        }
        else {
            setRotation(180);
        }
    }
    else if (coord.y == point.y) {
        if (coord.x > point.x) {
            setRotation(270);
        }
        else {
            setRotation(90);
        }
    }
    else {
        float slope = (point.y - coord.y)/(point.x - coord.x);
        float theta = (atan(slope) * 180)/PI;
        if (coord.x > point.x)
            theta = 180+theta;

        setRotation(theta+90);
    }
}

void PlayerShip::moveTo(sf::Vector2f point) {
    mDestination = point;

    float dx = getPosition().x - point.x;
    float dy = getPosition().y - point.y;

    mDistanceLeft = sqrt((dx*dx) + (dy*dy));
    mIsMoving = true;

    float rad = getRotation()-90;
    rad = (rad*PI)/180;

    float vx = SPEED * cos(rad);
    float vy = SPEED * sin(rad);

    mVelocity = sf::Vector2f(vx, vy);
}

void PlayerShip::fire(std::list<Missile *>& missiles) {
    if (mCooldown > 0) return;

    mCooldown = COOLDOWN;

    sf::Vector2f pos;
    Missile* missile;

    pos = getTransform().transformPoint(21, 0);
    missile = new Missile(getScreen(), this, false);
    missile->setPosition(pos);
    missile->setRotation(getRotation());
    missiles.push_back(missile);

    pos = getTransform().transformPoint(71, 0);
    missile = new Missile(getScreen(), this, false);
    missile->setPosition(pos);
    missile->setRotation(getRotation());
    missiles.push_back(missile);

    mSFX.play();
}

void PlayerShip::setHealth(int health) {
    if (health < 0) health = 0;
    if (health > 100) health = 100;

    mHealth = health;
}
