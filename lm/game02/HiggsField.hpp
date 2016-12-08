#pragma once

#include <SFML/Graphics.hpp>
#include "PhysicalEntity.hpp"
#include "Log.hpp"

namespace lmg02
{
class HiggsField
{
public:
    HiggsField(common::Log&);
    void add_entity(PhysicalEntity*);
    sf::Vector2f get_accel(const PhysicalEntity * const, float) const;
private:
    common::Log& log;
    sf::Vector2f
    other_entities_accel(const PhysicalEntity* const) const;
    std::vector<PhysicalEntity*> entities;
};
}
