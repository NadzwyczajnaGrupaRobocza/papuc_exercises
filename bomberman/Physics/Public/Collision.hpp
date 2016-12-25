#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "Collider.hpp"

namespace physics
{
using Colliders = std::vector<Collider>;

class Collision
{
public:
    Collision(std::size_t triggers_count, std::size_t colliders_count);

    void update();
    Collider& addTrigger(sf::Vector2f position, float width, float height);
    Collider& addStaticCollider(sf::Vector2f position, float width,
                                float height);
    Collider& addDynamicCollider(sf::Vector2f position, float width,
                                 float height);

private:
    void collidersVsTriggers();
    void collidersVsColliders();

    Collider createCollider(sf::Vector2f position, float width, float height);
    bool AABBvsAABB(const AABB&, const AABB&) const;
    // Manifold getCollisionAlignment(float x_overlap, float y_overlap,
    //                                sf::Vector2f from_static_to_dynamic) const;

private:
    Colliders _triggers;
    Colliders _dynamic_colliders;
    Colliders _static_colliders;
};
}
