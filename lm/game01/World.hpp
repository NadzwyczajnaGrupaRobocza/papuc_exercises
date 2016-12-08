#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <vector>

namespace lmg01
{
class World
{
public:
    World(sf::RenderWindow& target);
    void advance(const sf::Time& tick, const sf::Vector2f& playerMove);
private:
    std::vector<sf::CircleShape> createObstacles();
    void draw();
    void drawObstacles();
    void drawPlayer();
    void movePlayer(const sf::Vector2f&);
    sf::Vector2f validMovement(const sf::Vector2f&, const sf::CircleShape& obstacle) const;

    sf::RenderWindow& target;
    Board b;
    sf::CircleShape player;
    sf::Vector2f player_position;
    std::vector<sf::CircleShape> obstacle_container;
};

float dist_sqr(const sf::Vector2f& a, const sf::Vector2f b);
sf::Vector2f center(const sf::Shape& s);
float compute_scaling_factor(const sf::Vector2f& b, const sf::Vector2f& c, float d);
}
