#pragma once

#include <SFML/Graphics.hpp>

#include "AABB.hpp"
#include "Board.hpp"
#include "Entity.hpp"
#include "IBomberman.hpp"

namespace bomberman
{

using Shapes = std::vector<sf::RectangleShape>;
using Entities = std::vector<Entity>;
using Boundaries = std::vector<AABB>;

class Bomberman : public IBomberman
{
public:
    Bomberman();
    void run();

private:
    void updateInput();
    void updatePlayerInput();
    void updateMovement(float deltaTime);
    void movePlayer(const sf::Vector2f& transl);
    void triggerTest();
    void render();
    void renderShapes();
    void clearDisplay();
    void swapBuffer();

    void generateRandomnlyArrangedStaticEntities(const std::size_t count);
    void generateDynamicEntities(const std::size_t count);

     bool AABBvsAABB(const AABB&, const AABB&) const;

    sf::RenderWindow window;
    lmg01::Board board;
    const float baseSpeed = 200.f;
    const std::size_t static_entity_count = 260;
    const std::size_t dynamic_entity_count = 1;
    float bonusSpeed = 1.0f;
    sf::Vector2f movementDirection{0, 0};
    Shapes shapes;
    Boundaries static_triggers;
    Entities static_entities;
    Boundaries dynamic_colliders;
    Entities dynamic_entities;
};
}
