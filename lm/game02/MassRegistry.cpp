#include "MassRegistry.hpp"
#include <cmath>

namespace lmg02
{
void MassRegistry::add_entity(PhysicalEntity* e)
{
    entities.push_back(e);
}

sf::Vector2f MassRegistry::get_accel(const PhysicalEntity* const caller,
                                     float /*dt*/) const
{
    const auto& caller_state = caller->get_state();
    // constexpr auto friction_coeff = 1.f;
    sf::Vector2f base_accel{0.f, 0.f};
    sf::Vector2f large_mass_center{400.f, 300.f};

    sf::Vector2f direction = large_mass_center - caller_state.position;
    float length = std::hypot(direction.x, direction.y);
    sf::Vector2f accel_from_mass =
        direction * (1 / (length * length * length));
    float G = 0.6f;
    float large_mass = 2000000.f;
    accel_from_mass *= G * large_mass;
    base_accel += accel_from_mass;

    if (caller_state.position.x > 700.f)
    {
        auto pos_dif = 800.f - caller_state.position.x;
        auto factor = 100.f / (pos_dif * pos_dif);
        base_accel += (-1.f) * factor * caller_state.velocity;
        //(-1.f / pos_dif) * friction_coeff * caller_state.velocity;
    }
    if (caller_state.position.x < 100.f)
    {
        auto pos_dif = caller_state.position.x;
        auto factor = 100.f / (pos_dif * pos_dif);
        base_accel += (-1.f) * factor * caller_state.velocity;
    }
    if (caller_state.position.y > 500.f)
    {
        auto pos_dif = 600.f - caller_state.position.y;
        auto factor = 100.f / (pos_dif * pos_dif);
        base_accel += (-1.f) * factor * caller_state.velocity;
    }
    if (caller_state.position.y < 50.f)
    {
        auto pos_dif = caller_state.position.y;
        auto factor = 100.f / (pos_dif * pos_dif);
        base_accel += (-1.f) * factor * caller_state.velocity;
    }

    return base_accel;
    ;
}
}
