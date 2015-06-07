#include "BasicEnemy.hpp"
#include "Missile.hpp"

// Points per second
#define SPEED 50
// Canon cooldown in seconds
#define COOLDOWN 0.4
// Radar angle
#define RADAR_ANGLE 30
// Rotation speed
#define ANGULAR_VELOCITY 90
// Damage per missile
#define DAMAGE 2

float angle(GameObject* go1, GameObject* go2) {
    float result;

    sf::Vector2f coord = go1->getPosition();
    sf::Vector2f point = go2->getPosition();

    if (coord.x == point.x && coord.y == point.y) {
        return 0;
    }

    if (coord.x == point.x) {
        if (coord.y > point.y) {
            result = 0;
        }
        else {
            result = 180;
        }
    }
    else if (coord.y == point.y) {
        if (coord.x > point.x) {
            result = 270;
        }
        else {
            result = 90;
        }
    }
    else {
        float slope = (point.y - coord.y)/(point.x - coord.x);
        float theta = (atan(slope) * 180)/PI;
        if (coord.x > point.x)
            theta = 180+theta;

        result = theta+90;
    }

    return result;
}

BasicEnemy::BasicEnemy(Screen& screen)
    : GameObject(screen)
    , mCooldown(COOLDOWN)
    , mCanSee(false)
{
    mVertices.resize(4);
    getScreen().getGame().getResourceManager().loadSprite(this, 0, "enemyRed1.png", 0, 0);

    mSFX.setBuffer(*getScreen().getGame().getResourceManager().getSoundBuffer("sfx_laser1.ogg"));
    mSFX.setVolume(SFX_VOLUME);

//    mVelocity = sf::Vector2f(-50, -50);

    setOrigin(46, 35);
    setRotation(0);


    boundingPolygon.push_back(sf::Vector2f(10, 10));
    boundingPolygon.push_back(sf::Vector2f(0,  26));
    boundingPolygon.push_back(sf::Vector2f(11, 57));
    boundingPolygon.push_back(sf::Vector2f(81, 57));
    boundingPolygon.push_back(sf::Vector2f(92, 26));
    boundingPolygon.push_back(sf::Vector2f(82, 10));

    mHealthBar = new StatusBar2(getScreen());
}

void BasicEnemy::update(float dt) {
    GameObject::update(dt);
    setRotation(getRotation() + mAngularVelocity * dt);

    if (mCooldown > 0)
        mCooldown -= dt;
    if (mCooldown < 0)
        mCooldown = 0;

    if (mPlayerShip->isDead) {
        mCanSee = false;
        return;
    }

    float rotation = getRotation();
    float alpha = angle(this, mPlayerShip) - 180;
    if (alpha < 0) alpha = 360 + alpha;
    float diff = alpha - rotation;
    if (abs(alpha - rotation) < RADAR_ANGLE) {
        mCanSee = true;
        mAngularVelocity = diff;

        if (diff < 0)
            mAngularVelocity = -ANGULAR_VELOCITY;
        else
            mAngularVelocity = ANGULAR_VELOCITY;

        float rad = rotation+90;
        rad = (rad*PI)/180;

        float vx = SPEED * cos(rad);
        float vy = SPEED * sin(rad);

        mVelocity = sf::Vector2f(vx, vy);
    }
    else {
        mCanSee = false;
        mAngularVelocity = ANGULAR_VELOCITY;
        mVelocity = sf::Vector2f(0, 0);
    }
}

void BasicEnemy::drawHealthBar(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Transform transform;
    transform.translate(getPosition());
    transform.scale(getScale());

    sf::Transform originalTransform = states.transform;
    states.transform = states.transform.combine(transform);

    target.draw(*mHealthBar, states);

    states.transform = originalTransform;
}

void BasicEnemy::fire(std::list<Missile*>& missiles) {
    if (!mCanSee) return;
    if (mCooldown > 0) return;

    mCooldown = COOLDOWN;

    sf::Vector2f pos;
    Missile* missile;

    pos = getTransform().transformPoint(30, 80);
    missile = new Missile(getScreen(), this);
    missile->setPosition(pos);
    missile->setRotation(180+getRotation());
    missile->damage = DAMAGE;
    missiles.push_back(missile);

    pos = getTransform().transformPoint(70, 80);
    missile = new Missile(getScreen(), this);
    missile->setPosition(pos);
    missile->setRotation(180+getRotation());
    missile->damage = DAMAGE;
    missiles.push_back(missile);

    mSFX.play();
}
