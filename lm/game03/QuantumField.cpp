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

sf::Vector2f QuantumField::get_accel(const PointMass& caller) const
{
    sf::Vector2f base_accel{0.f, 0.f};

    if (&caller == player_object)
    {
        base_accel += user_input;
        user_input = {};
    }
    return base_accel;
}

void QuantumField::set_player_object(const PointMass* p_player_object)
{
    player_object = p_player_object;
}

void QuantumField::set_user_input(const sf::Vector2f& current_user_input)
{
    user_input = current_user_input;
}
}
