#pragma once
#include <SFML/Graphics.hpp>

namespace lmg01
{
class Board
{
public:
    Board();

    void drawOn(sf::RenderWindow&);
private:
    int N;
    int M;

};
}
