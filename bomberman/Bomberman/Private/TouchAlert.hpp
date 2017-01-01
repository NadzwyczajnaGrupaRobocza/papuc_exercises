#pragma once

#include <SFML/Graphics/Color.hpp>

#include "CollisionScript.hpp"

namespace bomberman
{
class Entity;
class TouchAlert : public physics::CollisionScript
{
public:
    TouchAlert(bomberman::Entity&, sf::Color);
    void onCollisionEnter(physics::Collider&) override;
    void onCollisionExit() override;

private:
    bomberman::Entity& _entity;
    sf::Color _base_color;
    sf::Color _touch_color;
};
}
