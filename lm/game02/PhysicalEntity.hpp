#pragma once

#include <SFML/Graphics.hpp>

namespace lmg02
{
class MassRegistry;
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
    PhysicalEntity(const sf::Vector2f&, const sf::Vector2f&, float, const MassRegistry&);

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
    State compute_next_state(float dt);
    Derivative evaluate(float dt, const Derivative& d);

    State current_state;
    State next_state;
    float mass;
    const MassRegistry& registry;
};

}
