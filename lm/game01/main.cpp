#include <SFML/Graphics.hpp>
#include <iostream>
#include "World.hpp"

sf::Vector2f processUserInput(float, sf::RenderWindow&);

int main(int /*argc*/, char** /*argv*/)
{
    sf::Vector2i screenSize{800, 600};
    float baseSpeed = 200.f;

    sf::RenderWindow mainWindow(sf::VideoMode(screenSize.x, screenSize.y), "myproject");
    mainWindow.setVerticalSyncEnabled(true);
    lmg01::World w(mainWindow.getView());
    w.draw(mainWindow);

    sf::Clock frameClock;

    while (mainWindow.isOpen())
    {
        sf::Time frameTick = frameClock.restart();

        auto movement = processUserInput(baseSpeed, mainWindow);
        w.advance(frameTick, movement);

        w.draw(mainWindow);

        mainWindow.display();
    }
}

sf::Vector2f processUserInput(float speed, sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

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

    return movement;
}
