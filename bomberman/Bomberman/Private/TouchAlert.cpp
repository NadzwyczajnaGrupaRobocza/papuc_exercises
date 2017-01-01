#include "TouchAlert.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "Entity.hpp"

namespace bomberman
{
TouchAlert::TouchAlert(Entity& entity, sf::Color touch_color)
    : _entity{entity}, _base_color{entity.get_shape().getFillColor()},
      _touch_color{touch_color}
{
}

void TouchAlert::onCollisionEnter(physics::Collider&)
{
    _entity.get_shape().setFillColor(_touch_color);
}

void TouchAlert::onCollisionExit()
{
    _entity.get_shape().setFillColor(_base_color);
}
}
