#include "World.hpp"
#include "fp_manip.hpp"
#include <algorithm>
#include <random>

namespace lmg02
{
World::World(common::Log& logInit)
    : log{logInit}, registry{log},
      entities{
          PhysicalEntity{
              log, {200.f, 100.f}, {40.f, -30.f}, 10000000.f, registry},
          PhysicalEntity{
              log, {599.f, 500.f}, {0.f, -1.f}, 20000000000.f, registry},
          PhysicalEntity{
              log, {300.f, 500.f}, {100.f, -10.f}, 500000.f, registry}}
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> x_distr(20.f, 780.f);
    std::uniform_real_distribution<float> y_distr(20.f, 580.f);
    std::uniform_real_distribution<float> x_vee(-.5f, .5f);
    std::uniform_real_distribution<float> y_vee(-.5f, .5f);
    std::uniform_real_distribution<float> mass_dist(50000.f,
                                                    200000.f);
    std::generate_n(std::back_inserter(entities), 100, [&]() {
        return PhysicalEntity{log,
                              {x_distr(gen), y_distr(gen)},
                              {x_vee(gen), y_vee(gen)},
                              mass_dist(gen),
                              registry};
    });

    for (auto& e : entities)
    {
        registry.add_entity(&e);
    }
}

void World::advance(const sf::Time& tick, const sf::Vector2f& /*playerMove*/)
{
    for (auto& e : entities)
    {
        e.prepare_next_pos(tick.asSeconds());
    }

    for (auto& e : entities)
    {
        e.detect_colision(mass_box);
    }
}

void World::display_on(sf::RenderTarget& target)
{
    target.clear();
    Board b{target.getView()};
    b.drawOn(target);
    sf::RectangleShape mass{{40.f, 40.f}};
    mass.setFillColor(sf::Color::Yellow);
    mass.setPosition({380.f, 280.f});
    target.draw(mass);
    for (auto& e : entities)
    {
        e.draw(target);
    }
}
}
