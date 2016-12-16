#include "World.hpp"
#include "fp_manip.hpp"
#include <algorithm>
#include <random>

namespace lmg01
{
World::World(sf::View view_init)
    : current_view{view_init}, b{current_view},
      player{sf::Vector2f{20.f, 20.f}}, player_position{50.f, 50.f},
      obstacle_container{createObstacles()}
{
    player.setFillColor(sf::Color::Black);
}

std::vector<sf::RectangleShape> World::createObstacles()
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> x_distr(
        20.f, current_view.getSize().x - 20.f);
    std::uniform_real_distribution<float> y_distr(
        20.f, current_view.getSize().y - 20.f);
    std::uniform_real_distribution<float> radius_distr(10.f, 50.f);

    std::vector<sf::RectangleShape> obstacles;
    std::generate_n(std::back_inserter(obstacles), 30, [&]() {
        sf::RectangleShape rect{
            sf::Vector2f{radius_distr(gen), radius_distr(gen)}};
        rect.setPosition(x_distr(gen), y_distr(gen));
        rect.setFillColor(sf::Color::Blue);
        return rect;
    });
    return obstacles;
}

void World::draw(sf::RenderTarget& target)
{
    b.drawOn(target);
    drawObstacles(target);
    drawPlayer(target);
}

void World::drawObstacles(sf::RenderTarget& target)
{
    std::for_each(obstacle_container.begin(), obstacle_container.end(),
                  [&](const auto& ob) { target.draw(ob); });
}

void World::drawPlayer(sf::RenderTarget& target)
{
    player.setPosition(player_position);
    target.draw(player);
}

void World::movePlayer(const sf::Vector2f& transl)
{
    auto currentTranslation{transl};

    if (sf::FloatRect{{0.f, 0.f},
                      current_view.getSize() - sf::Vector2f{40.f, 40.f}}
            .contains(player_position + currentTranslation))
    {
        player_position += currentTranslation;
    }
}
}
