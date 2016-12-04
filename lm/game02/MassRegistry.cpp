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
    sf::Vector2f base_accel{0.f, 0.f};
    sf::Vector2f large_mass_center{400.f, 300.f};

    sf::Vector2f direction = large_mass_center - caller_state.position;
    float length =
        std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f accel_from_mass = direction * (1 / (length * length * length));
    float G = 0.6f;
    float large_mass = 2000000.f;
    accel_from_mass *= G * large_mass;
    base_accel += accel_from_mass;

    if (caller_state.position.x > 750.f)
    {
        base_accel += {-100.f, 0.f};
    }
    if (caller_state.position.x < 50.f)
    {
        base_accel += {100.f, 0.f};
    }
    if (caller_state.position.y > 550.f)
    {
        base_accel += {0.f, -100.f};
    }
    if (caller_state.position.y < 50.f)
    {
        base_accel += {0.f, 150.f};
    }

    return base_accel;
    ;
}
}
