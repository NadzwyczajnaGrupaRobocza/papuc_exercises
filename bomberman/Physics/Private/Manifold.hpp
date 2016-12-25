#pragma once

#include <SFML/System/Vector2.hpp>

namespace physics
{
struct Manifold
{
    sf::Vector2f normal;
    float penetration;
};
}
