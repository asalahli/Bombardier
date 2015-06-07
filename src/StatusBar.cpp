#include "StatusBar.hpp"

StatusBar::StatusBar(Screen& screen)
    : GameObject(screen)
{
    mVertices.resize(24);

    // Shadow
    getScreen().getGame().getResourceManager().loadSprite(
        this, 0, "barHorizontal_shadow_left.png", 0, 0);

    float offset = mVertices[1].position.x;

    getScreen().getGame().getResourceManager().loadSprite(
        this, 1, "barHorizontal_shadow_mid.png", mVertices[1].position.x, mVertices[1].position.y);

    mVertices[5].position.x = offset+200;
    mVertices[6].position.x = offset+200;

    getScreen().getGame().getResourceManager().loadSprite(
        this, 2, "barHorizontal_shadow_right.png", mVertices[5].position.x, mVertices[5].position.y);

    // Bar
    getScreen().getGame().getResourceManager().loadSprite(
        this, 3, "barHorizontal_green_left.png", 0, 0);

    getScreen().getGame().getResourceManager().loadSprite(
        this, 4, "barHorizontal_green_mid.png", mVertices[13].position.x, mVertices[13].position.y);

    mVertices[17].position.x = offset+100;
    mVertices[18].position.x = offset+100;

    getScreen().getGame().getResourceManager().loadSprite(
        this, 5, "barHorizontal_green_right.png", mVertices[17].position.x, mVertices[17].position.y);
}

void StatusBar::setHealth(int health) {
    if (health < 0) health = 0;
    if (health > 100) health = 100;

    mHealth = health;

    float offset = mVertices[1].position.x;

    if (mHealth == 0) offset = 0;

    mVertices[13].position.x = offset;
    mVertices[14].position.x = offset;

    mVertices[16].position.x = offset;
    mVertices[17].position.x = mHealth*2+offset;
    mVertices[18].position.x = mHealth*2+offset;
    mVertices[19].position.x = offset;

    mVertices[20].position.x = mHealth*2+offset;
    mVertices[21].position.x = mHealth*2+offset+offset;
    mVertices[22].position.x = mHealth*2+offset+offset;
    mVertices[23].position.x = mHealth*2+offset;
}
