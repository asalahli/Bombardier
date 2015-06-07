#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "SFML/Graphics.hpp"
#include "Screen.hpp"
#include <list>

#define PI 3.14159265359
#define SFX_VOLUME 40

class ResourceManager;

class GameObject : public sf::Drawable, public sf::Transformable {
friend class ResourceManager;
protected:
    Screen& mScreen;

    sf::VertexArray mVertices;

    float mDirection;
    sf::Vector2f mVelocity;
    sf::Vector2f mAcceleration;

    std::list<GameObject*> mChildren;

public:
    GameObject(Screen& screen);

    Screen& getScreen() const { return mScreen; };

    bool isDead;
    std::list<sf::Vector2f> boundingPolygon;
    sf::Vector2f getVelocity() { return mVelocity; };
    void setVelocity(float vx, float vy) { mVelocity = sf::Vector2f(vx, vy); };

    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // GAME_OBJECT_H
