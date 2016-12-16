#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <vector>

namespace lmg01
{
class World
{
public:
    World(sf::View);
    void draw(sf::RenderTarget&);
private:
    std::vector<sf::RectangleShape> createObstacles();
    void drawObstacles(sf::RenderTarget&);

    sf::View current_view;
    std::vector<sf::RectangleShape> obstacle_container;
};
}
