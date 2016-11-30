#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.hpp"

int main(int /*argc*/, char** /*argv*/)
{

    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "myproject");
    mainWindow.setVerticalSyncEnabled(true);
    lmg01::Board b;

    while (mainWindow.isOpen())
    {
        b.drawOn(mainWindow);
        mainWindow.display();

        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    std::cout << "UP\n";
                    b.movePlayer(sf::Vector2i{0, -1});
                    break;
                case sf::Keyboard::Down:
                    std::cout << "DOWN\n";
                    b.movePlayer(sf::Vector2i{0, 1});
                    break;
                case sf::Keyboard::Left:
                    std::cout << "LEFT\n";
                    b.movePlayer(sf::Vector2i{-1, 0});
                    break;
                case sf::Keyboard::Right:
                    std::cout << "RIGHT\n";
                    b.movePlayer(sf::Vector2i{1, 0});
                    break;
                default:
                    (void)0;
                }
            }
        }
    }
}
