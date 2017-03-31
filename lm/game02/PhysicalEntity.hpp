#pragma once

#include <SFML/Graphics.hpp>
#include "Log.hpp"

namespace lmg02
{
class HiggsField;
struct State
{
    sf::Vector2f position;
    sf::Vector2f velocity;
};

struct Derivative
{
    sf::Vector2f delta_pos;
    sf::Vector2f delta_vee;
};

class PhysicalEntity
{
public:
    PhysicalEntity(common::Log&, const sf::Vector2f&, const sf::Vector2f&, float, const HiggsField&);

    void prepare_next_pos(float);
    void detect_colision(const sf::FloatRect&);
    sf::Vector2f gravitational_pull_from(const PhysicalEntity&) const;
    void draw(sf::RenderTarget&);

    const State& get_state() const
    {
        return current_state;
    }

    float get_mass() const
    {
        return mass;
    }

private:
    common::Log& log;
    State compute_next_state(float dt);
    Derivative evaluate(float dt, const Derivative& d);

    State current_state;
    State next_state;
    float mass;
    const HiggsField& registry;
};

}
