#pragma once
#include "PhysicalEntity.hpp"

namespace lmg03
{
class CollisionDetector
{
public:
    void compute_collisions(std::vector<PhysicalEntity>&);
private:
    bool collistion_occured_between(const PhysicalEntity&, const PhysicalEntity&);
    void recompute_positions(PhysicalEntity& e1, PhysicalEntity& e2);

    float _last_moved_fraction;
};

}
