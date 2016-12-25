#pragma once

#include <SFML/System/Vector2.hpp>

namespace sf
{
class RectangleShape;
}

namespace physics
{
class Collider;
}

namespace bomberman
{
class Entity
{
public:
    Entity() = delete;
    Entity(sf::RectangleShape&, physics::Collider&);
    sf::RectangleShape& get_shape();
    physics::Collider& get_collider();

    void update();
    void move(sf::Vector2f translation);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape& _shape;
    physics::Collider& _collider;
};
}
