#pragma once
#include <SFML/System/Vector2.hpp>
#include <type_traits>

namespace lmg03
{

struct PointMass
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float mass;
};
}

//static_assert(std::is_pod<lmg03::PointMass>::value, "PointMass should be a POD");
