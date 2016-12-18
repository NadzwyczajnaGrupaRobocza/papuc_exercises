#include "Collision.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <gsl/gsl_assert>

#include "Entity.hpp"

namespace physics
{
Collision::Collision(std::size_t triggers_count, std::size_t colliders_count)
{
    triggers.reserve(triggers_count);
    colliders.reserve(colliders_count);
}

void Collision::update()
{
    collidersVsTriggers();
    collidersVsColliders();
}

void Collision::collidersVsTriggers()
{
    boost::for_each(colliders, [this](auto& collider) {
        boost::for_each(triggers, [this, &collider](auto const& trigger) {
            Expects(trigger.entity != nullptr);
            if (AABBvsAABB(collider, trigger))
            {
                // TODO: replace this code to use entity.onTrigger(collider)
                trigger.entity->get_shape().setFillColor(sf::Color::Red);
            }
            else
            {
                trigger.entity->get_shape().setFillColor(sf::Color::Blue);
            }
        });
    });
}

void Collision::collidersVsColliders()
{
    // TODO:
}

AABB& Collision::addTrigger(sf::Vector2f position, float width, float height)
{
    triggers.emplace_back(createAABB(position, width, height));
    return triggers.back();
}

AABB& Collision::addCollider(sf::Vector2f position, float width, float height)
{
    colliders.emplace_back(createAABB(position, width, height));
    return colliders.back();
}

AABB Collision::createAABB(sf::Vector2f position, float width, float height)
{
    AABB aabb;
    aabb.x_coord = position.x;
    aabb.y_coord = position.y;
    aabb.width = width;
    aabb.height = height;
    aabb.entity = nullptr;
    return aabb;
}

bool Collision::AABBvsAABB(const AABB& a, const AABB& b) const
{
    if (a.x_coord > (b.x_coord + b.width) || (a.x_coord + a.width) < b.x_coord)
    {
        return false;
    }

    if (a.y_coord > (b.y_coord + b.height) ||
        (a.y_coord + a.height) < b.y_coord)
    {
        return false;
    }

    return true;
}
}
