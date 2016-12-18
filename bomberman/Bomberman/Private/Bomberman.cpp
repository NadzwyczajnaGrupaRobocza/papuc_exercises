#include "Bomberman.hpp"

#include <algorithm>
#include <boost/range/algorithm/for_each.hpp>
#include <gsl/gsl_assert>
#include <random>

namespace bomberman
{
Bomberman::Bomberman()
    : window{sf::VideoMode(800, 600), "bomberman"}, board{window.getView()},
      collision{static_entity_count, dynamic_entity_count}
{
    window.setVerticalSyncEnabled(true);

    shapes.reserve(static_entity_count + dynamic_entity_count);
    generateRandomnlyArrangedStaticEntities(static_entity_count);
    generateDynamicEntities(dynamic_entity_count);
}

void Bomberman::run()
{
    sf::Clock frameClock;
    while (window.isOpen())
    {
        sf::Time frameTick = frameClock.restart();

        updateInput();
        updateMovement(frameTick.asSeconds());
        updatePhysics();
        updateRender();
    }
}

void Bomberman::updateInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }
    }
    updatePlayerInput();
}

void Bomberman::updatePlayerInput()
{
    movementDirection = sf::Vector2f{0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        movementDirection.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        movementDirection.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        movementDirection.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        movementDirection.x = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        bonusSpeed = 0.5f;
    }
    else
    {
        bonusSpeed = 1.0f;
    }
}

void Bomberman::updateMovement(float deltaTime)
{
    movePlayer(movementDirection * baseSpeed * bonusSpeed * deltaTime);
}

void Bomberman::movePlayer(const sf::Vector2f& transl)
{
    // TODO: for more dynamic entities it will be invalid
    Expects(dynamic_entities.size() == 1);
    auto& player = dynamic_entities.back();

    auto& p_shape = player.get_shape();

    if (sf::FloatRect{{0.f, 0.f},
                      window.getView().getSize() - sf::Vector2f{20.f, 20.f}}
            .contains(p_shape.getPosition() + transl))
    {
        const auto& new_position = player.get_shape().getPosition() + transl;
        player.get_shape().setPosition(new_position);
        player.get_aabb().x_coord = new_position.x;
        player.get_aabb().y_coord = new_position.y;
    }
}

void Bomberman::updateRender()
{
    clearDisplay();
    renderShapes();
    swapBuffer();
}

void Bomberman::updatePhysics()
{
    collision.update();
}

void Bomberman::renderShapes()
{
    board.drawOn(window);
    boost::for_each(shapes,
                    [this](auto const& entity) { window.draw(entity); });
}

void Bomberman::clearDisplay()
{
    window.clear(sf::Color::Black);
}

void Bomberman::swapBuffer()
{
    window.display();
}

void Bomberman::generateDynamicEntities(const std::size_t)
{
    dynamic_entities.reserve(1);

    float x = 0.0f;
    float y = 0.0f;
    float w = 20.0f;
    float h = 20.0f;
    shapes.emplace_back(sf::Vector2f{w, h});
    auto& player = shapes.back();
    player.setFillColor(sf::Color::Black);
    player.setPosition(x, y);

    auto& collider = collision.addCollider(sf::Vector2f(x, y), w, h);
    dynamic_entities.emplace_back(player, collider);
    collider.entity = &dynamic_entities.back();
}

void Bomberman::generateRandomnlyArrangedStaticEntities(const std::size_t count)
{
    static_entities.reserve(count);

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> x_distr(20.f,
                                                  window.getSize().x - 20.f);
    std::uniform_real_distribution<float> y_distr(20.f,
                                                  window.getSize().y - 20.f);
    std::uniform_real_distribution<float> radius_distr(10.f, 50.f);

    for (std::remove_const_t<decltype(count)> i = 0; i < count; ++i)
    {
        float w = radius_distr(gen);
        float h = radius_distr(gen);
        shapes.emplace_back(sf::Vector2f{w, h});
        float x = x_distr(gen);
        float y = y_distr(gen);
        shapes.back().setPosition(x, y);
        shapes.back().setFillColor(sf::Color::Blue);

        auto& trigger = collision.addTrigger(sf::Vector2f(x, y), w, h);
        static_entities.emplace_back(shapes.back(), trigger);
        trigger.entity = &static_entities.back();
    }
}
}

int main()
{
    bomberman::Bomberman bomberman;
    bomberman.run();
}
