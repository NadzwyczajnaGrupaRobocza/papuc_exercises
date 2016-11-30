#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"

namespace lmg01
{
class World
{
public:
    World(sf::RenderWindow& target);
    void advance(const sf::Time& tick, const sf::Vector2f& playerMove);
private:
    void draw();
    void drawPlayer();
    void movePlayer(const sf::Vector2f&);

    sf::RenderWindow& target;
    Board b;
    sf::Vector2f playerPosition;

};
}
