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
    return {100.f, 100.f};
}
}
