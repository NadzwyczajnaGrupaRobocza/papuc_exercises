#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "AABB.hpp"

namespace physics
{
using Boundaries = std::vector<AABB>;

class Collision
{
public:
    Collision(std::size_t triggers_count, std::size_t colliders_count);

    void update();
    AABB& addTrigger(sf::Vector2f position, float width, float height);
    AABB& addCollider(sf::Vector2f position, float width, float height);

private:
    void collidersVsTriggers();
    void collidersVsColliders();

    AABB createAABB(sf::Vector2f position, float width, float height);
    bool AABBvsAABB(const AABB&, const AABB&) const;

private:
    Boundaries triggers;
    Boundaries colliders;
};
}
