#pragma once

namespace sf
{
class RectangleShape;
}

namespace physics
{
struct AABB;
}

namespace bomberman
{
class Entity
{
public:
    Entity(sf::RectangleShape&, physics::AABB&);
    sf::RectangleShape& get_shape();
    physics::AABB& get_aabb();

private:
    sf::RectangleShape& _shape;
    physics::AABB& _aabb;
};
}
