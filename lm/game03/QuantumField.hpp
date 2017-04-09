#pragma once

#include "Log.hpp"
#include "fp_manip.hpp"
#include "PointMass.hpp"
#include <SFML/Graphics.hpp>

namespace lmg03
{
class QuantumField
{
public:
    QuantumField(common::Log&);
    sf::Vector2f get_accel(const PointMass&) const;
    sf::Vector2f friction(const PointMass& caller) const;

    void set_player_object(const PointMass* player_object);
    void set_user_input(const sf::Vector2f&);

private:
    common::Log& log;
    const PointMass* player_object;
    mutable sf::Vector2f user_input;
};
}
