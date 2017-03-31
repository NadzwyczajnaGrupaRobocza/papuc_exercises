#pragma once
#include <SFML/Graphics.hpp>

namespace lmg03
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
