#include "World.hpp"
#include "fp_manip.hpp"
#include <algorithm>
#include <random>

namespace lmg01
{
World::World(sf::RenderWindow& targetInit)
    : target{targetInit}, b{target.getView()}, player{20.f},
      player_position{50.f, 50.f}, obstacle_container{createObstacles()}
{
    // obstacle.setPosition(230.f, 145.f);
    // obstacle.setFillColor(sf::Color::Blue);
    player.setFillColor(sf::Color::Red);
    draw();
}

void World::advance(const sf::Time& tick, const sf::Vector2f& playerMove)
{
    movePlayer(playerMove * tick.asSeconds());
    draw();
}

std::vector<sf::CircleShape> World::createObstacles()
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> x_distr(
        20.f, target.getView().getSize().x - 20.f);
    std::uniform_real_distribution<float> y_distr(
        20.f, target.getView().getSize().y - 20.f);
    std::uniform_real_distribution<float> radius_distr(10.f, 50.f);

    std::vector<sf::CircleShape> obstacles;
    std::generate_n(std::back_inserter(obstacles),
                    30,
                    [&]()
                    {
                        sf::CircleShape cs{radius_distr(gen)};
                        cs.setPosition(x_distr(gen), y_distr(gen));
                        cs.setFillColor(sf::Color::Blue);
                        return cs;
                    });
    return obstacles;
}

void World::draw()
{
    target.clear(sf::Color::Black);
    b.drawOn(target);
    drawObstacles();
    drawPlayer();
    target.display();
}

void World::drawObstacles()
{
    std::for_each(obstacle_container.begin(), obstacle_container.end(),
                  [this](const auto& ob) { target.draw(ob); });
}

void World::drawPlayer()
{
    player.setPosition(player_position);
    target.draw(player);
}

void World::movePlayer(const sf::Vector2f& transl)
{
    auto currentTranslation{transl};

    for (const auto& obstacle : obstacle_container)
        currentTranslation = validMovement(currentTranslation, obstacle);

    if (sf::FloatRect{{0.f, 0.f},
                      target.getView().getSize() - sf::Vector2f{40.f, 40.f}}
            .contains(player_position + currentTranslation))
        player_position += currentTranslation;
}

sf::Vector2f World::validMovement(const sf::Vector2f& translation,
                                  const sf::CircleShape& obstacle) const
{
    auto beginPlayerPos{center(player)};
    auto obstaclePos{center(obstacle)};
    auto endPlayerPos{center(player) + translation};

    auto r = player.getRadius();
    auto R = obstacle.getRadius();
    auto rR = r + R;
    auto dist_s = dist_sqr(endPlayerPos, obstaclePos);

    auto scaling_factor = 1.f;
    if (dist_s < rR * rR)
    {
        scaling_factor = compute_scaling_factor(
            translation, obstaclePos - beginPlayerPos, r + R);
    }

    return translation * scaling_factor;
}

float dist_sqr(const sf::Vector2f& a, const sf::Vector2f b)
{
    auto xx = a.x - b.x;
    auto yy = a.y - b.y;
    return xx * xx + yy * yy;
}

sf::Vector2f center(const sf::Shape& s)
{
    auto bb = s.getGlobalBounds();
    return {bb.left + 0.5f * bb.width, bb.top + 0.5f * bb.height};
}

float compute_scaling_factor(const sf::Vector2f& b, const sf::Vector2f& c,
                             float d)
{
    auto factor = 0.f;
    if (fp::equal(b.x * b.y, 0.f))
    {
        factor = std::max(c.x * c.x + c.y * c.y - d * d, 0.f);

        if (fp::not_equal(b.x, 0.f))
            factor /= b.x * c.x;

        if (fp::not_equal(b.y, 0.f))
            factor /= b.y * c.y;
    }

    return factor;
}
}
