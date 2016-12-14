#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace sfml_help
{
inline sf::Vector2f from_1_to_2_unit(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    auto dir = v2 - v1;
    float len = std::hypot(dir.x, dir.y);
    return {dir.x / len, dir.y / len};
}

inline float length(const sf::Vector2f& v)
{
    return std::hypot(v.x, v.y);
}

inline float length_squared(const sf::Vector2f& v)
{
    return v.x * v.x + v.y * v.y;
}
}
