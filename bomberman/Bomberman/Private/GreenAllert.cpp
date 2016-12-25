#include "GreenAllert.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "Entity.hpp"

namespace bomberman
{
GreenAllert::GreenAllert(Entity& entity)
    : _entity{entity}, _base_color{entity.get_shape().getFillColor()}
{
}

void GreenAllert::onCollisionEnter(physics::Collider&)
{
    _entity.get_shape().setFillColor(sf::Color::Green);
}

void GreenAllert::onCollisionExit()
{
    _entity.get_shape().setFillColor(_base_color);
}
}
