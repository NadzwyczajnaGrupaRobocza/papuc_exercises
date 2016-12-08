#pragma once
#include <SFML/Graphics.hpp>

namespace lmg01
{
class Board
{
public:
    Board(const sf::View&);

    void drawOn(sf::RenderWindow&);

private:
    void drawEmptyBoard(sf::RenderWindow&);

    sf::View currentView;
    int N;
    int M;
};
}
