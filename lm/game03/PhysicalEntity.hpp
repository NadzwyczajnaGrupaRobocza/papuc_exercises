#pragma once

#include "Log.hpp"
#include "QuantumField.hpp"
#include "PointMass.hpp"
#include <SFML/Graphics.hpp>

namespace lmg03
{

struct Derivative
{
    sf::Vector2f delta_pos;
    sf::Vector2f delta_vee;
};

class PhysicalEntity
{
public:
    PhysicalEntity(common::Log&, const sf::Vector2f&, const sf::Vector2f&,
                   float, const QuantumField&);

    void prepare_next_pos(float);
    void detect_colision(const sf::FloatRect&);
    sf::Vector2f gravitational_pull_from(const PhysicalEntity&) const;
    void draw(sf::RenderTarget&);

    const PointMass& get_state() const
    {
        return current_state;
    }

private:
    common::Log& log;
    PointMass compute_next_state(float dt);
    Derivative evaluate(float dt, const Derivative& d);

    PointMass current_state;
    PointMass next_state;

    const QuantumField& force_source;
};
}
