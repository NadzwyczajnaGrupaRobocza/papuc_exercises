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
    virtual ~PhysicalEntity() = default;

    void prepare_next_pos(float);
    void detect_colision(const sf::FloatRect&);
    void advance_to_next_state();
    void draw(sf::RenderTarget&);

    const PointMass& get_state() const;
    const PointMass& get_next_state() const;
    void set_next_state(const PointMass&);
    float get_radius() const;

protected:
    PointMass getCurrentState() const;

private:
    common::Log& log;
    PointMass compute_next_state(float dt);
    Derivative evaluate(float dt, const Derivative& d);
    virtual sf::Vector2f calculateAcceleration() const;
    virtual sf::Color getColor() const;

    PointMass current_state;
    PointMass next_state;

    float radius;

    const QuantumField& force_source;
};
}
