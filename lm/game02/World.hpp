#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <vector>
#include "PhysicalEntity.hpp"
#include "MassRegistry.hpp"

namespace lmg02
{
class World
{
public:
    World();
    void advance(const sf::Time& , const sf::Vector2f& );
    void display_on(sf::RenderTarget&);

private:
    MassRegistry registry;
    std::vector<PhysicalEntity> entities;
};

}
