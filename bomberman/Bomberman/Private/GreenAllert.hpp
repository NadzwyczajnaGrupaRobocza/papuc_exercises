#pragma once

#include <SFML/Graphics/Color.hpp>

#include "CollisionScript.hpp"

namespace bomberman
{
class Entity;
class GreenAllert : public physics::CollisionScript
{
public:
    explicit GreenAllert(bomberman::Entity&);
    void onCollisionEnter(physics::Collider&) override;
    void onCollisionExit() override;

private:
    bomberman::Entity& _entity;
    sf::Color _base_color;
};
}
