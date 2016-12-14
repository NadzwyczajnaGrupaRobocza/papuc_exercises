#include "QuantumField.hpp"
#include "Log.hpp"
#include "PhysicalConstants.hpp"
#include "sfml_help.hpp"
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <cmath>

using namespace sfml_help;

namespace lmg03
{
QuantumField::QuantumField(common::Log& log_init) : log{log_init}
{
}

sf::Vector2f QuantumField::get_accel(const PointMass& /*caller*/) const
{
    sf::Vector2f base_accel{0.f, 0.f};

    return base_accel;
}



}
