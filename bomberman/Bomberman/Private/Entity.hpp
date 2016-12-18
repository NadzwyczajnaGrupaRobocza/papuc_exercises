#pragma once

namespace sf
{
class RectangleShape;
}

namespace bomberman
{
struct AABB;
class Entity
{
public:
    Entity(sf::RectangleShape&, AABB&);
    sf::RectangleShape& get_shape();
    AABB& get_aabb();

private:
    sf::RectangleShape& _shape;
    AABB& _aabb;
};
}
