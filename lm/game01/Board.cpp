#include "Board.hpp"
#include <iostream>

namespace lmg01
{
Board::Board(int maxX, int maxY) : N{maxX}, M{maxY}
{
}

void Board::drawOn(sf::RenderWindow& target)
{
        drawEmptyBoard(target);
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

}
