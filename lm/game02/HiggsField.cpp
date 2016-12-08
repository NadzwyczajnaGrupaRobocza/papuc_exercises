#include "HiggsField.hpp"
#include "Log.hpp"
#include "PhysicalConstants.hpp"
#include "sfml_help.hpp"
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <cmath>

using namespace sfml_help;

namespace lmg02
{
HiggsField::HiggsField(common::Log& logInit) : log{logInit}
{
}
void HiggsField::add_entity(PhysicalEntity* e)
{
    entities.push_back(e);
}

sf::Vector2f boundry_accel(const State& s);
sf::Vector2f compute_boundry_accel(float pos_dif,
                                   const sf::Vector2f& velocity);
sf::Vector2f compute_gravitational_attraction(const PhysicalEntity* const,
                                              const PhysicalEntity* const);

// sf::Vector2f compute_central_mass_accel(const sf::Vector2f& position,
//                                         float other_mass);
// sf::Vector2f compute_central_mass_accel(const sf::Vector2f&
// other_position,
//                                         float other_mass)
// {
//     sf::Vector2f large_mass_center{400.f, 300.f};
//     sf::Vector2f direction = large_mass_center - other_position;
//     sf::Vector2f direction_unit =
//         from_1_to_2_unit(other_position, large_mass_center);
//     double large_mass = 200000000000.f;

//     float numerator = static_cast<float>(GRAVITATIONAL_CONSTANT *
//                                          large_mass * other_mass);
//     float denominator = length_squared(direction);

//     return direction_unit * numerator / denominator;
// }

sf::Vector2f HiggsField::get_accel(const PhysicalEntity* const caller,
                                     float /*dt*/) const
{
    //const auto& caller_state = caller->get_state();
    sf::Vector2f base_accel{0.f, 0.f};

    // base_accel += compute_central_mass_accel(caller_state.position,
    //                                          caller->get_mass());
    // base_accel += boundry_accel(caller_state);
    base_accel += other_entities_accel(caller);

    return base_accel;
}

sf::Vector2f
HiggsField::other_entities_accel(const PhysicalEntity* const caller) const
{
    using boost::adaptors::filtered;
    sf::Vector2f accel{0.f, 0.f};
    boost::for_each(
        entities | filtered([&](const auto& e) { return e != caller; }),
        [&](const auto& e) {
            accel += caller->gravitational_pull_from(*e);
        });
    log.info() << "other entities accel: {" << accel.x << ", " << accel.y << "}";
    return accel;
}

sf::Vector2f boundry_accel(const State& s)
{
    sf::Vector2f base_accel{0.f, 0.f};
    if (s.position.x > 600.f)
    {
        base_accel +=
            compute_boundry_accel(800.f - s.position.x, s.velocity);
    }
    if (s.position.x < 200.f)
    {
        base_accel += compute_boundry_accel(s.position.x, s.velocity);
    }
    if (s.position.y > 400.f)
    {
        base_accel +=
            compute_boundry_accel(600.f - s.position.y, s.velocity);
    }
    if (s.position.y < 200.f)
    {
        base_accel += compute_boundry_accel(s.position.y, s.velocity);
    }

    return base_accel;
}

sf::Vector2f compute_boundry_accel(float pos_dif,
                                   const sf::Vector2f& velocity)
{
    auto factor = pos_dif > std::numeric_limits<float>::epsilon()
                      ? 1000.f / (pos_dif * pos_dif)
                      : 100000.f;
    return velocity * (-1.f) * factor;
}
}
