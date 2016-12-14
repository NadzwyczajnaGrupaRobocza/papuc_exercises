#pragma once

#include "Log.hpp"
#include "PointMass.hpp"
#include <SFML/Graphics.hpp>

namespace lmg03
{
class QuantumField
{
public:
    QuantumField(common::Log&);
    sf::Vector2f get_accel(const PointMass&) const;

private:
    common::Log& log;
};
}
