#pragma once
#include "Board.hpp"
#include "Log.hpp"
#include "PhysicalEntity.hpp"
#include "QuantumField.hpp"
#include <SFML/Graphics.hpp>
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
    common::Log& log;
    QuantumField force_source;
    std::vector<PhysicalEntity> entities;
};
}
