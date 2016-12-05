#include "World.hpp"
#include "fp_manip.hpp"
#include <algorithm>
#include <random>

namespace lmg02
{
World::World()
    : entities{PhysicalEntity{{200.f, 100.f}, {40.f, -30.f}, registry},
               PhysicalEntity{{700.f, 500.f}, {0.f, -100.f}, registry}}
{
}

void World::advance(const sf::Time& tick,
                    const sf::Vector2f& /*playerMove*/)
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
