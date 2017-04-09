#pragma once
#include "PhysicalEntity.hpp"

namespace lmg03
{
class CollisionDetector
{
public:
    void compute_collisions(const sf::Time&, std::vector<PhysicalEntity>&);
private:
    bool collistion_occured_between(const PhysicalEntity&, const PhysicalEntity&);
    void recompute_positions(PhysicalEntity&, PhysicalEntity&);
    void resolve_colistion_with_world_boundry(PhysicalEntity&);

    float _last_moved_fraction;
    sf::Time _current_tick;
};

}
