#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.hpp"

int main(int /*argc*/, char** /*argv*/)
{

    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "myproject");

    while (mainWindow.isOpen())
    {
        lmg01::Board b;
        b.drawOn(mainWindow);
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
            }
        }
        mainWindow.display();
    }
}
