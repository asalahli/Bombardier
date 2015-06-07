#ifndef COLLISION_H
#define COLLISION_H

#include "SFML/Audio.hpp"
#include "GameObject.hpp"

sf::Vector2f checkCollision(const GameObject* go1, const GameObject* go2);

#endif // COLLISION_H
