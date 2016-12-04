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
    PhysicalEntity(const sf::Vector2f&, const sf::Vector2f&, const MassRegistry&);

    void advance(float);
    void draw(sf::RenderTarget&);

    const State& get_state() const
    {
        return current_state;
    }

private:
    void integrate(float dt);
    Derivative evaluate(float dt, const Derivative& d);
    State current_state;
    float mass;
    const MassRegistry& registry;
};

}
