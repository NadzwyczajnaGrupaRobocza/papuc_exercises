#pragma once

#include <SFML/Graphics.hpp>
#include "PhysicalEntity.hpp"

namespace lmg02
{
class MassRegistry
{
public:
    void add_entity(PhysicalEntity*);
    sf::Vector2f get_accel(const PhysicalEntity * const, float) const;
private:
    std::vector<PhysicalEntity*> entities;
};
}
