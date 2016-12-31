#pragma once

#include "PhysicalEntity.hpp"

namespace lmg03
{

class LogicalEntity : public PhysicalEntity
{
public:
    LogicalEntity(common::Log&, const sf::Vector2f&, const sf::Vector2f&,
                  float, const QuantumField&);

};
}
