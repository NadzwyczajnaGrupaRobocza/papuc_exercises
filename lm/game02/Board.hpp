#pragma once
#include <SFML/Graphics.hpp>

namespace lmg02
{
class Board
{
public:
    Board(const sf::View&);

    void drawOn(sf::RenderTarget&);

private:
    void drawEmptyBoard(sf::RenderTarget&);

    sf::View currentView;
    int N;
    int M;
};
}
