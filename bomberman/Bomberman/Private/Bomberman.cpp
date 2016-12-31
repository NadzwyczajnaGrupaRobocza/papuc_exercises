#include "Bomberman.hpp"

#include <algorithm>
#include <boost/range/algorithm/for_each.hpp>
#include <gsl/gsl_assert>
#include <memory>
#include <random>

#include <cassert>
#include <fstream>
#include <iostream>

#include "GreenAllert.hpp"
#include "RedAllert.hpp"

namespace bomberman
{
Bomberman::Bomberman()
    : _window{sf::VideoMode(800, 600), "bomberman"}, _board{_window.getView()},
      _collision{0, _static_entity_count, _dynamic_entity_count},
      _player{nullptr}
{
    _window.setVerticalSyncEnabled(false);

    _shapes.reserve(_static_entity_count + _dynamic_entity_count);
    generateRandomnlyArrangedStaticEntities(_static_entity_count);
    generateDynamicEntities(_dynamic_entity_count);
}

void Bomberman::run()
{
    sf::Clock frameClock;
    while (_window.isOpen())
    {
        sf::Time frameTick = frameClock.restart();

        updateEntities();
        updateInput();
        updateMovement(frameTick.asSeconds());
        updatePhysics();
        updateRender();
    }
}

void Bomberman::updateEntities()
{
    boost::for_each(_static_entities, [](auto& entity) { entity.update(); });
    boost::for_each(_dynamic_entities, [](auto& entity) { entity.update(); });
    // TODO(abergard): remove destroyed entities here
}

void Bomberman::updateInput()
{
    sf::Event event{};
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape))
        {
            _window.close();
        }
    }
    updatePlayerInput();
}

void Bomberman::updatePlayerInput()
{
    _movementDirection = sf::Vector2f{0, 0};
    _bonusSpeed = 1.0f;
    updatePlayerKeyboard();
    updatePlayerXbox360Pad();
}

void Bomberman::updatePlayerKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        _movementDirection.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        _movementDirection.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        _movementDirection.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        _movementDirection.x = 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        _bonusSpeed = 2.5f;
    }
}

void Bomberman::updatePlayerXbox360Pad()
{
    if (sf::Joystick::isConnected(0))
    {
        sf::Vector2f move_speed{
            sf::Joystick::getAxisPosition(0, sf::Joystick::X),
            sf::Joystick::getAxisPosition(0, sf::Joystick::Y)};

        // std::cerr << "x:" << move_speed.x << ",y:" << move_speed.y << "\n";

        float treshold = 40;
        if (move_speed.x > treshold)
        {
            _movementDirection.x = 1;
        }
        if (move_speed.x < -treshold)
        {
            _movementDirection.x = -1;
        }
        if (move_speed.y > treshold)
        {
            _movementDirection.y = 1;
        }
        if (move_speed.y < -treshold)
        {
            _movementDirection.y = -1;
        }

        if (std::fabs(move_speed.x) > 79.0f || std::fabs(move_speed.y) > 79.0f)
        {
            _bonusSpeed = 2.5f;
        }
    }
}

void Bomberman::updateMovement(float deltaTime)
{
    movePlayer(_movementDirection * _baseSpeed * _bonusSpeed * deltaTime);
}

void Bomberman::movePlayer(const sf::Vector2f& transl)
{
    Expects(_player != nullptr);
    if (sf::FloatRect{{0.f, 0.f},
                      _window.getView().getSize() - sf::Vector2f{20.f, 20.f}}
            .contains(_player->getPosition() + transl))
    {
        _player->move(transl);
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
    _collision.update();
}

void Bomberman::renderShapes()
{
    _board.drawOn(_window);
    boost::for_each(_shapes,
                    [this](auto const& entity) { _window.draw(entity); });
}

void Bomberman::clearDisplay()
{
    _window.clear(sf::Color::Black);
}

void Bomberman::swapBuffer()
{
    _window.display();
}

void Bomberman::generateDynamicEntities(const std::size_t& count)
{
    _dynamic_entities.reserve(count);
    {
        float x = 0.0f;
        float y = 0.0f;
        float w = 30.0f;
        float h = 30.0f;
        _shapes.emplace_back(sf::Vector2f{w, h});
        auto& player = _shapes.back();
        player.setFillColor(sf::Color::Black);
        player.setPosition(x, y);

        auto& collider =
            _collision.addDynamicCollider(sf::Vector2f(x, y), w, h);
        _dynamic_entities.emplace_back(player, collider);
        collider.set_entity(_dynamic_entities.back());
        _player = &_dynamic_entities.back();
    }
}

void Bomberman::generateRandomnlyArrangedStaticEntities(
    const std::size_t& count)
{
    _static_entities.reserve(count);
    generateMap(count);
    // generateRandomnlyStaticTriggerEntities(count / 2);
    // generateRandomnlyStaticColliderEntities(count / 2);
}
void Bomberman::generateRandomnlyStaticTriggerEntities(const std::size_t& count)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> x_distr(
        20.f, static_cast<float>(_window.getSize().x) - 20.f);
    std::uniform_real_distribution<float> y_distr(
        20.f, static_cast<float>(_window.getSize().y) - 20.f);
    std::uniform_real_distribution<float> radius_distr(10.f, 50.f);

    for (std::size_t i = 0; i < count; i += 2)
    {
        float w = radius_distr(gen);
        float h = radius_distr(gen);
        _shapes.emplace_back(sf::Vector2f{w, h});
        float x = x_distr(gen);
        float y = y_distr(gen);
        _shapes.back().setPosition(x, y);

        if (i % 2 == 0)
        {
            auto& trigger = _collision.addTrigger(sf::Vector2f(x, y), w, h);
            _static_entities.emplace_back(_shapes.back(), trigger);
            trigger.set_entity(_static_entities.back());
            trigger.attachScript(
                std::make_unique<RedAllert>(_static_entities.back()));
            _shapes.back().setFillColor(sf::Color::Blue);
        }
    }
}
void Bomberman::generateRandomnlyStaticColliderEntities(
    const std::size_t& count)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> x_distr(
        20.f, static_cast<float>(_window.getSize().x) - 20.f);
    std::uniform_real_distribution<float> y_distr(
        20.f, static_cast<float>(_window.getSize().y) - 20.f);
    std::uniform_real_distribution<float> radius_distr(10.f, 50.f);

    for (std::size_t i = 1; i < count; i += 2)
    {
        float w = radius_distr(gen);
        float h = radius_distr(gen);
        _shapes.emplace_back(sf::Vector2f{w, h});
        float x = x_distr(gen);
        float y = y_distr(gen);
        _shapes.back().setPosition(x, y);

        if (i % 2 == 1)
        {
            auto& collider =
                _collision.addStaticCollider(sf::Vector2f(x, y), w, h);

            _static_entities.emplace_back(_shapes.back(), collider);

            collider.set_entity(_static_entities.back());
            _shapes.back().setFillColor(sf::Color::Magenta);

            collider.attachScript(
                std::make_unique<GreenAllert>(_static_entities.back()));
        }
    }
}
void Bomberman::generateMap(const std::size_t&)
{
    // int x = static_cast<int>(sqrt(count));
    int tile_size = 50;
    generateUnDestructibleWalls(14 * tile_size, 11 * tile_size, tile_size);
}

void Bomberman::generateUnDestructibleWalls(int width, int height,
                                            int tile_size)
{
    for (int x = tile_size; x < width; x += 2 * tile_size)
    {
        for (int y = tile_size; y < height; y += 2 * tile_size)
        {
            _shapes.emplace_back(sf::Vector2f(tile_size, tile_size));
            auto& shape = _shapes.back();
            auto& collider = _collision.addStaticCollider(sf::Vector2f(x, y),
                                                          tile_size, tile_size);
            _static_entities.emplace_back(shape, collider);
            auto& entity = _static_entities.back();
            entity.setPosition(sf::Vector2f(x, y));
            collider.set_entity(entity);
            shape.setFillColor(sf::Color::Magenta);

            collider.attachScript(std::make_unique<GreenAllert>(entity));
        }
    }
}
}

int main()
{
    bomberman::Bomberman bomberman;
    bomberman.run();
}
