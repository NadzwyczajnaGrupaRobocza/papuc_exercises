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
    void movePlayer(const sf::Vector2f&);
private:
    std::vector<sf::RectangleShape> createObstacles();
    void drawObstacles(sf::RenderTarget&);
    void drawPlayer(sf::RenderTarget&);

    sf::View current_view;
    Board b;
    sf::RectangleShape player;
    sf::Vector2f player_position;
    std::vector<sf::RectangleShape> obstacle_container;
};
}
