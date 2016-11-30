#include "Board.hpp"
#include <iostream>

namespace lmg01
{
Board::Board() : N{10}, M{10}
{
}

void Board::drawOn(sf::RenderWindow& target)
{
    if (needsRedraw)
    {
        target.clear(sf::Color::Black);
        drawEmptyBoard(target);
        drawPlayer(target);
        needsRedraw = false;
    }
}

void Board::drawEmptyBoard(sf::RenderWindow& target)
{
    for (auto i = 0; i < N; i++)
    {
        for (auto j = 0; j < M; j++)
        {
            float x_pos = 50.0f * static_cast<float>(i);
            float y_pos = 50.0f * static_cast<float>(j);
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(50.0f, 50.0f));
            rectangle.setOutlineColor(sf::Color::Red);
            rectangle.setOutlineThickness(1);
            rectangle.setPosition(50.0f + x_pos, 50.0f + y_pos);
            target.draw(rectangle);
        }
    }
}

void Board::drawPlayer(sf::RenderWindow& target)
{
    float x_pos = 50.0f * static_cast<float>(playerPos.x);
    float y_pos = 50.0f * static_cast<float>(playerPos.y);
    sf::CircleShape player{20.0f};
    player.setPosition(55.0f + x_pos, 55.f + y_pos);
    player.setFillColor(sf::Color::Red);
    target.draw(player);
}

void Board::movePlayer(const sf::Vector2i& transl)
{
    playerPos += transl;

    while (playerPos.x < 0) playerPos.x += N;
    while (playerPos.y < 0) playerPos.y += M;

    if (playerPos.x >= N) playerPos.x %= N;
    if (playerPos.y >= M) playerPos.y %= M;

    needsRedraw = true;
}
}
