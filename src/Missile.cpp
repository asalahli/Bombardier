#include "Missile.hpp"
#include "ResourceManager.hpp"

#define SPEED 1000

Missile::Missile(Screen& screen, GameObject* o, bool enemy)
    : GameObject(screen)
    , owner(o)
    , damage(20)
{
    mVertices.resize(4);
    if (enemy)
        getScreen().getGame().getResourceManager().loadSprite(this, 0, "laserRed02.png", 0, 0);
    else
        getScreen().getGame().getResourceManager().loadSprite(this, 0, "laserGreen05.png", 0, 0);

    boundingPolygon.push_back(sf::Vector2f(0, 0));
    boundingPolygon.push_back(sf::Vector2f(0, 36));
    boundingPolygon.push_back(sf::Vector2f(8, 36));
    boundingPolygon.push_back(sf::Vector2f(8, 0));
}

void Missile::update(float dt) {
    if (mVelocity.x == 0 && mVelocity.y == 0) {
        float rad = getRotation()-90;
        rad = (rad*PI)/180;

        float vx = SPEED * cos(rad);
        float vy = SPEED * sin(rad);

        mVelocity = sf::Vector2f(vx, vy);
    }
    GameObject::update(dt);
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    GameObject::draw(target, states);
}
