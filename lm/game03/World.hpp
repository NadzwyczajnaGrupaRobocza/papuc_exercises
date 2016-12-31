#pragma once
#include "Board.hpp"
#include "CollisionDetector.hpp"
#include "Log.hpp"
#include "PhysicalEntity.hpp"
#include "QuantumField.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace lmg03
{
class World
{
public:
    World(common::Log&);
    void advance(const sf::Time&, const sf::Vector2f&);
    void display_on(sf::RenderTarget&);

private:
    using Entities = std::vector<std::unique_ptr<PhysicalEntity>>;
    common::Log& log;
    QuantumField force_source;
    Entities entities;
    CollisionDetector collision_detector;
};
}
