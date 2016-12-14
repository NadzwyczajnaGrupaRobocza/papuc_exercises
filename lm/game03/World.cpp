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
              log, {200.f, 100.f}, {0.f, 0.f}, 10000000.f, force_source},
          PhysicalEntity{
              log, {599.f, 500.f}, {0.f, 0.f}, 20000000000.f, force_source},
          PhysicalEntity{
              log, {300.f, 500.f}, {0.f, 0.f}, 500000.f, force_source}}
{
    force_source.set_player_object(&(entities[0].get_state()));
}

void World::advance(const sf::Time& tick, const sf::Vector2f& playerMove)
{
    force_source.set_user_input(playerMove);
    for (auto& e : entities)
    {
        e.prepare_next_pos(tick.asSeconds());
    }

    for (auto& e : entities)
    {
        e.advance_ignore_colistions();
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
