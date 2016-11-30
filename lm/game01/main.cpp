#include <SFML/Graphics.hpp>
#include <iostream>
#include "World.hpp"

int main(int /*argc*/, char** /*argv*/)
{

    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "myproject");
    mainWindow.setVerticalSyncEnabled(true);
    lmg01::World w(mainWindow);

    sf::Clock frameClock;

    float speed = 40.f;

    while (mainWindow.isOpen())
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
            }

            sf::Time frameTick = frameClock.restart();

            sf::Vector2f movement{0.f, 0.f};
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                movement.y -= speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                movement.y += speed;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                movement.x -= speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                movement.x += speed;
            }

            w.advance(frameTick, movement);
        }
    }
}
