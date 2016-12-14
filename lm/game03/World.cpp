#include "World.hpp"
#include "fp_manip.hpp"
#include <algorithm>
#include <random>

namespace lmg03
{
World::World(common::Log& log_init)
    : log{log_init}, force_source{log},
      entities{
          PhysicalEntity{
              log, {200.f, 100.f}, {40.f, -30.f}, 10000000.f, force_source},
          PhysicalEntity{
              log, {599.f, 500.f}, {0.f, -1.f}, 20000000000.f, force_source},
          PhysicalEntity{
              log, {300.f, 500.f}, {100.f, -10.f}, 500000.f, force_source}}
{

}

void World::advance(const sf::Time& tick, const sf::Vector2f& /*playerMove*/)
{
    for (auto& e : entities)
    {
        e.prepare_next_pos(tick.asSeconds());
    }
}

void World::display_on(sf::RenderTarget& target)
{
    target.clear();
    Board b{target.getView()};
    b.drawOn(target);
    for (auto& e : entities)
    {
        e.draw(target);
    }
}
}
