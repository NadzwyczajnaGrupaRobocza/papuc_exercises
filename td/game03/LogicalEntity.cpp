#include "LogicalEntity.hpp"

namespace lmg03
{
LogicalEntity::LogicalEntity(common::Log& log_init,
                             const sf::Vector2f& position_init,
                             const sf::Vector2f& velocity_init,
                             float mass_init,
                             const QuantumField& force_source_init,
                             const PointMass& playerInit)
    : PhysicalEntity{log_init, position_init, velocity_init, mass_init,
                     force_source_init},
      log{log_init}, player{playerInit}
{
    log.debug() << player.mass;
}
sf::Vector2f LogicalEntity::calculateAcceleration() const
{
    const auto target_x = player.position.x;
    const auto target_y = player.position.y;
    const auto own_x = getCurrentState().position.x;
    const auto own_y = getCurrentState().position.y;
    float verticalSpeed{};
    float horizontalSpeed{};
    if (target_x > own_x)
    {
        verticalSpeed = 100.f;
    }
    if (target_x < own_x)
    {
        verticalSpeed = -100.f;
    }
    if (target_y > own_y)
    {
        horizontalSpeed = 100.f;
    }
    if (target_y < own_y)
    {
        horizontalSpeed = -100.f;
    }
    return {verticalSpeed, horizontalSpeed};
}

sf::Color LogicalEntity::getColor() const
{
    return sf::Color::Green;
}
}
