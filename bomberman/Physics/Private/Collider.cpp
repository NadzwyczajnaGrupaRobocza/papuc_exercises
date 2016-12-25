#include "Collider.hpp"

#include <boost/range/algorithm/for_each.hpp>
#include <cassert>
#include <utility>

#include "CollisionScript.hpp"
#include "Entity.hpp"

#include <iostream>

namespace physics
{
Collider::Collider(AABB aabb) : _aabb{aabb}, _entity{nullptr}, _script{nullptr}
{
    assert(_collisions.size() == 0 &&
           "collisions in collider should should be empty");
}

Collider::Collider(Collider&& collider)
    : _aabb{collider._aabb}, _collisions{std::move(collider._collisions)},
      _entity{collider._entity}, _script{std::move(collider._script)}
{

    collider._entity = nullptr;
}

void Collider::operator=(Collider&& collider)
{
    _aabb = collider._aabb;
    _collisions = std::move(collider._collisions);
    _entity = collider._entity;
    collider._entity = nullptr;
    _script = std::move(collider._script);

}

void Collider::setPosition(sf::Vector2f position)
{
    _aabb.x = position.x;
    _aabb.y = position.y;
}

AABB& Collider::get_aabb()
{
    return _aabb;
}

bomberman::Entity& Collider::get_entity() const
{
    assert(_entity != nullptr && "Entity should be set");
    return *_entity;
}

void Collider::set_entity(bomberman::Entity& entity)
{
    _entity = &entity;
}

void Collider::addCollision(Collider& collider)
{
    _collisions.push_back(&collider);
}

void Collider::attachScript(std::unique_ptr<CollisionScript> script)
{
    _script = std::move(script);
}

void Collider::runScript()
{
    if (_script != nullptr)
    {

        if (not _collisions.empty())
        {
            boost::for_each(_collisions, [this](auto& collider) {
                assert(collider != nullptr &&
                       "Collider should not be destroyed!");
                _script->onCollisionEnter(*collider);
            });
        }
        else
        {
            _script->onCollisionExit();
        }
    }
    _collisions.clear();
}
}
