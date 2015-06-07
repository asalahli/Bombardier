#include "Explosion.hpp"

#define DURATION 2.0f
#define FRAME_COUNT 24

Explosion::Explosion(Screen& screen, GameObject* deadObj, float x, float y, bool last)
    : GameObject(screen)
    , mFrame(0)
    , mElapsed(0)
    , mLast(last)
    , mDeadObj(deadObj)
{
    setPosition(deadObj->getPosition());
    setRotation(deadObj->getRotation());
    setOrigin(45, 45);
    setScale(2, 2);

    mVertices.resize(4);
    getScreen().getGame().getResourceManager().loadSprite(this, 0, "explosion0.png", 0, 0);

    mSFX.setBuffer(*getScreen().getGame().getResourceManager().getSoundBuffer("sfx_explosion.ogg"));
    mSFX.setVolume(SFX_VOLUME-25);
    mSFX.play();
}

Explosion::~Explosion() {
    if (mLast) getScreen().getGame().gameOver();
    else delete mDeadObj;
}

void Explosion::update(float dt) {
    mElapsed += dt;
    if (mElapsed > DURATION) {
        isDead = true;
        return;
    }

    int newFrame = floor(FRAME_COUNT * (mElapsed / DURATION));
    if (newFrame != mFrame && newFrame < 10) {
        std::string frame = "explosion0.png";
        frame[9] = mFrame + 48;
        getScreen().getGame().getResourceManager().loadSprite(this, 0, frame, 0, 0);
    }

    mFrame = newFrame;
}

void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (mFrame < 10) {
        GameObject::draw(target, states);
    }
}

void Explosion::drawDeadObject(sf::RenderTarget& target, sf::RenderStates states) const {
    if (mFrame < 5) {
        target.draw(*mDeadObj, states);
    }
}
