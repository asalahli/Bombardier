#include "GameObject.hpp"
#include "sqlite3.h"

GameObject::GameObject(Screen& screen)
    : mScreen(screen)
    , isDead(false)
{
    mVertices.setPrimitiveType(sf::Quads);
    /*
        Temporary
    */
    mVelocity = sf::Vector2f(0, 0);
    mAcceleration = sf::Vector2f(0, 0);
}

void GameObject::update(float dt) {
    mVelocity += mAcceleration * dt;
    setPosition(getPosition() + (mVelocity * dt));
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Transform originalTransform = states.transform;
    states.transform = states.transform.combine(getTransform());

    for (GameObject* child : mChildren) {
        target.draw(*child, states);
    }

    target.draw(mVertices, states);

    sf::RenderStates boundState;
    boundState.transform = states.transform;

    #ifdef DEBUG
        sf::VertexArray bound;
        bound.setPrimitiveType(sf::LinesStrip);
        bound.resize(boundingPolygon.size()+1);
        int i=0;
        for (sf::Vector2f p : boundingPolygon) {
            bound[i].position = p;
            bound[i].color = sf::Color::Green;
            i++;
        }
        bound[i].position = boundingPolygon.front();
        bound[i].color = sf::Color::Green;

        target.draw(bound, boundState);
    #endif // DEBUG

    states.transform = originalTransform;
}
