#include "Bomberman.hpp"

#include <algorithm>
#include <boost/range/algorithm/for_each.hpp>
#include <gsl/gsl_assert>
#include <random>

namespace bomberman
{
Bomberman::Bomberman()
    : window{sf::VideoMode(800, 600), "bomberman"}, board{window.getView()}
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
        triggerTest();
        render();
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        movementDirection.y = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        movementDirection.y = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        movementDirection.x = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
    auto& player =
        dynamic_entities
            .back(); // TODO: for more dynamic entities it will be invalid

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

void Bomberman::render()
{
    clearDisplay();
    renderShapes();
    swapBuffer();
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

void Bomberman::generateDynamicEntities(const std::size_t count)
{
    dynamic_colliders.reserve(count);
    dynamic_entities.reserve(1);

    float x = 0.0f;
    float y = 0.0f;
    float w = 20.0f;
    float h = 20.0f;
    shapes.emplace_back(sf::Vector2f{w, h});
    auto& player = shapes.back();
    player.setFillColor(sf::Color::Black);
    player.setPosition(x, y);

    AABB aabb;
    aabb.x_coord = x;
    aabb.y_coord = y;
    aabb.width = w;
    aabb.height = h;

    dynamic_colliders.emplace_back(std::move(aabb));
    dynamic_entities.emplace_back(player, dynamic_colliders.back());
    dynamic_colliders.back().entity = &dynamic_entities.back();
}

void Bomberman::generateRandomnlyArrangedStaticEntities(const std::size_t count)
{
    static_triggers.reserve(count);
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

        AABB aabb;
        aabb.x_coord = x;
        aabb.y_coord = y;
        aabb.width = w;
        aabb.height = h;

        static_triggers.emplace_back(std::move(aabb));
        static_entities.emplace_back(shapes.back(), static_triggers.back());
        static_triggers.back().entity = &static_entities.back();
    }
}

void Bomberman::triggerTest()
{
    boost::for_each(dynamic_entities, [this](auto& dynamic_entity) {
        auto& aabb = dynamic_entity.get_aabb();
        boost::for_each(static_triggers, [this, &aabb](auto const& trigger) {

            Expects(trigger.entity != nullptr);
            auto& entity = *trigger.entity;

            if (AABBvsAABB(aabb, trigger))
            {
                entity.get_shape().setFillColor(sf::Color::Red);
            }
            else
            {
                entity.get_shape().setFillColor(sf::Color::Blue);
            }
        });
    });
}

bool Bomberman::AABBvsAABB(const AABB& a, const AABB& b) const
{
    if (a.x_coord > (b.x_coord + b.width) || (a.x_coord + a.width) < b.x_coord)
    {
        return false;
    }

    if (a.y_coord > (b.y_coord + b.height) ||
        (a.y_coord + a.height) < b.y_coord)
    {
        return false;
    }

    return true;
}
}

int main()
{
    bomberman::Bomberman bomberman;
    bomberman.run();
}
