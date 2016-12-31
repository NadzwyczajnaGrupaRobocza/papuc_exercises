#include "World.hpp"
#include "fp_manip.hpp"
#include <algorithm>
#include <random>

namespace lmg03
{
World::World(common::Log& log_init)
    : log{log_init}, force_source{log},
      entities{PhysicalEntity{
                   log, {200.f, 300.f}, {0.f, 0.f}, 1000.f, force_source},
               PhysicalEntity{
                   log, {599.f, 500.f}, {0.f, 0.f}, 200.f, force_source},
               PhysicalEntity{
                   log, {300.f, 500.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {550.f, 300.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {570.f, 315.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {570.f, 285.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {600.f, 320.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {600.f, 280.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {630.f, 320.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {630.f, 280.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {660.f, 320.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {660.f, 280.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {690.f, 320.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {690.f, 280.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {690.f, 360.f}, {0.f, 0.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {50.f, 50.f}, {10.f, 10.f}, 500.f, force_source},
               PhysicalEntity{
                   log, {780.f, 360.f}, {0.f, 0.f}, 500.f, force_source}},
      collision_detector{}
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

    collision_detector.compute_collisions(tick, entities);

    for (auto& e : entities)
    {
        e.advance_to_next_state();
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
