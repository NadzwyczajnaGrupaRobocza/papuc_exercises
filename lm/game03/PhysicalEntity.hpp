#pragma once

#include "Log.hpp"
#include "PointMass.hpp"
#include "QuantumField.hpp"
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
    void advance_to_next_state();
    void draw(sf::RenderTarget&);

    const PointMass& get_state() const;
    const PointMass& get_next_state() const;
    void set_next_state(const PointMass&);
    float get_radius() const;

private:
    PointMass compute_next_state(float dt);
    Derivative evaluate(float dt, const Derivative& d);

    PointMass current_state;
    PointMass next_state;

    float radius;

    const QuantumField& force_source;
};
}
