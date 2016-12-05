#include "MassRegistry.hpp"
#include <cmath>

namespace lmg02
{
void MassRegistry::add_entity(PhysicalEntity* e)
{
    entities.push_back(e);
}
sf::Vector2f compute_boundry_accel(float pos_dif,
                                   const sf::Vector2f& velocity);
sf::Vector2f compute_boundry_accel(float pos_dif,
                                   const sf::Vector2f& velocity)
{
    auto factor = pos_dif > std::numeric_limits<float>::epsilon() ? 1000.f / (pos_dif * pos_dif) : 100000.f;
    return velocity * (-1.f) * factor;
}
sf::Vector2f compute_central_mass_accel(const sf::Vector2f& position);
sf::Vector2f compute_central_mass_accel(const sf::Vector2f& position)
{
    sf::Vector2f large_mass_center{400.f, 300.f};

    sf::Vector2f direction = large_mass_center - position;
    float length = std::hypot(direction.x, direction.y);

    float G = 0.6f;
    float large_mass = 2000000.f;

    return G * large_mass * direction * (1 / (length * length * length));

}

sf::Vector2f MassRegistry::get_accel(const PhysicalEntity* const caller,
                                     float /*dt*/) const
{
    const auto& caller_state = caller->get_state();
    sf::Vector2f base_accel{0.f, 0.f};

    base_accel += compute_central_mass_accel(caller_state.position);

    if (caller_state.position.x > 600.f)
    {
        base_accel += compute_boundry_accel(800.f - caller_state.position.x,
                                            caller_state.velocity);
    }
    if (caller_state.position.x < 200.f)
    {
        base_accel += compute_boundry_accel(caller_state.position.x,
                                            caller_state.velocity);
    }
    if (caller_state.position.y > 400.f)
    {
        base_accel += compute_boundry_accel(600.f - caller_state.position.y,
                                            caller_state.velocity);
    }
    if (caller_state.position.y < 200.f)
    {
        base_accel += compute_boundry_accel(caller_state.position.y,
                                            caller_state.velocity);
    }

    return base_accel;
}
}
