#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

#include "AABB.hpp"
#include "CollisionScript.hpp"

namespace bomberman
{
class Entity;
}

namespace physics
{
class Collider
{
public:
    Collider() = delete;
    explicit Collider(AABB);
    Collider(const Collider&) = delete;
    Collider(Collider&&);

    void operator=(const Collider&) = delete;
    void operator=(Collider&&);

    void setPosition(sf::Vector2f position);
    AABB& get_aabb();
    bomberman::Entity& get_entity() const;
    void set_entity(bomberman::Entity&);
    void addCollision(Collider&);
    void attachScript(std::unique_ptr<CollisionScript>);
    void runScript();

private:
    AABB _aabb;
    std::vector<Collider*> _collisions;
    bomberman::Entity* _entity;
    std::unique_ptr<CollisionScript> _script;
};
}
