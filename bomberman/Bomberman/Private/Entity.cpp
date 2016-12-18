#include "Entity.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "AABB.hpp"

namespace bomberman
{
Entity::Entity(sf::RectangleShape& shape, physics::AABB& aabb)
    : _shape{shape}, _aabb{aabb}
{
}

sf::RectangleShape& Entity::get_shape()
{
    return _shape;
}

physics::AABB& Entity::get_aabb()
{
    return _aabb;
}
}
