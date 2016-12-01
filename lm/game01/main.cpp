#include "World.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
    sf::Vector2i screenSize{800, 600};
    sf::RenderWindow mainWindow(sf::VideoMode(screenSize.x, screenSize.y), "myproject");
    mainWindow.setVerticalSyncEnabled(true);
    lmg01::World w(mainWindow);

    sf::Clock frameClock;

    float baseSpeed = 200.f;

    while (mainWindow.isOpen())
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
            }
        }

        sf::Time frameTick = frameClock.restart();
        float speed{baseSpeed};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            speed *= .5f;
        }

        sf::Vector2f movement{0.f, 0.f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            movement.y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            movement.y += speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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
