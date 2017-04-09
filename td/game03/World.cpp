#include "World.hpp"
#include "LogicalEntity.hpp"
#include "fp_manip.hpp"
#include <algorithm>
#include <random>

namespace lmg03
{

World::World(common::Log& log_init)
    : log{log_init}, force_source{log}, entities{}, collision_detector{}
{

    entities.emplace_back(std::make_unique<PhysicalEntity>(
        log, sf::Vector2f{200.f, 300.f}, sf::Vector2f{0.f, 0.f}, 1000.f,
        force_source));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{599.f, 500.f}, sf::Vector2f{0.f, 0.f}, 200.f,
        force_source, entities[0]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{300.f, 500.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[1]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{550.f, 300.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[2]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{570.f, 315.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[3]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{570.f, 285.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[4]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{600.f, 320.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[5]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{600.f, 280.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[6]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{630.f, 320.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[7]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{630.f, 280.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[8]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{660.f, 320.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[9]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{660.f, 280.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[10]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{690.f, 320.f}, sf::Vector2f{0000.f, 0000.f},
        5000.f, force_source, entities[11]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{690.f, 280.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[12]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{690.f, 360.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[13]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{780.f, 360.f}, sf::Vector2f{0.f, 0.f}, 500.f,
        force_source, entities[14]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{50.f, 50.f}, sf::Vector2f{10.f, 10.f}, 500.f,
        force_source, entities[15]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{290.f, 290.f}, sf::Vector2f{20.f, 20.f}, 600.f,
        force_source, entities[16]->get_state()));
    entities.emplace_back(std::make_unique<LogicalEntity>(
        log, sf::Vector2f{10.f, 890.f}, sf::Vector2f{00000.f, 00000.f},
        600.f, force_source, entities[17]->get_state()));
    force_source.set_player_object(&(entities[0]->get_state()));
}

void World::advance(const sf::Time& tick, const sf::Vector2f& playerMove)
{
    force_source.set_user_input(playerMove);
    for (auto& e : entities)
    {
        e->prepare_next_pos(tick.asSeconds());
    }

    collision_detector.compute_collisions(tick, entities);

    for (auto& e : entities)
    {
        e->advance_to_next_state();
    }
}

void World::display_on(sf::RenderTarget& target)
{
    target.clear();
    Board b{target.getView()};
    b.drawOn(target);
    for (auto& e : entities)
    {
        e->draw(target);
    }
}
}
