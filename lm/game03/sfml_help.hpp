#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace sfml_help
{

inline float length(const sf::Vector2f& v)
{
    return std::hypot(v.x, v.y);
}

inline float length_squared(const sf::Vector2f& v)
{
    return v.x * v.x + v.y * v.y;
}

inline sf::Vector2f unit(const sf::Vector2f& v)
{
    auto l = length(v);
    return {v.x / l, v.y / l};
}

inline sf::Vector2f from_1_to_2_unit(const sf::Vector2f& v1,
                                     const sf::Vector2f& v2)
{
    auto dir = v2 - v1;
    return unit(dir);
}


inline float dist(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return length(v1 - v2);
}

inline float dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

inline sf::Vector2f invert_parallel_component(const sf::Vector2f& v, const sf::Vector2f& base)
{
    const float v_in_base_len = dot(base, v);
    return v - (2.f * v_in_base_len * base);
}

}
