#include "World.hpp"

namespace lmg01
{
World::World(sf::RenderWindow& targetInit)
    : target{targetInit}, b{10, 6}, playerPosition{50.f, 50.f}
{
    draw();
}

void World::advance(const sf::Time& tick, const sf::Vector2f& playerMove)
{
    movePlayer(playerMove * tick.asSeconds());
    draw();
}

void World::draw()
{
    target.clear(sf::Color::Black);;
    b.drawOn(target);
    drawPlayer();
    target.display();
}

void World::drawPlayer()
{
    sf::CircleShape player{20.0f};
    player.setPosition(playerPosition);
    player.setFillColor(sf::Color::Red);
    target.draw(player);
}

void World::movePlayer(const sf::Vector2f& transl)
{
    playerPosition += transl;

    // while (playerPos.x < 0) playerPos.x += N;
    // while (playerPos.y < 0) playerPos.y += M;

    // if (playerPos.x >= N) playerPos.x %= N;
    // if (playerPos.y >= M) playerPos.y %= M;
}

}
