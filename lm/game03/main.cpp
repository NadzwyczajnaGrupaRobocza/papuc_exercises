#include "World.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "StreamLog.hpp"

sf::Vector2f processUserInput(float baseSpeed, sf::RenderWindow& window);

int main(int /*argc*/, char** /*argv*/)
{
    sf::Vector2i screenSize{800, 600};
    sf::RenderWindow mainWindow(sf::VideoMode(screenSize.x, screenSize.y),
                                "myproject");
    mainWindow.setVerticalSyncEnabled(true);
    std::stringstream s;
    common::StreamLog slog{s};
    lmg03::World w{slog};

    sf::Clock frameClock;

    constexpr float baseSpeed = 200.f;
    constexpr float frameDuration = 1.f / 60.f;

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

        const auto duration = frameClock.getElapsedTime();
        if (duration.asSeconds() < frameDuration)
            continue;

        frameClock.restart();

        sf::Vector2f movement{processUserInput(baseSpeed, mainWindow)};
        w.advance(duration, movement);

        w.display_on(mainWindow);
        mainWindow.display();
    }
}

sf::Vector2f processUserInput(float speed, sf::RenderWindow& window)
{
    auto view = window.getView();
    sf::Vector2f movement{0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        speed *= .5f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        view.move(0.f, -5.f);
        movement.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        view.move(0.f, 5.f);
        movement.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        view.move(-5.f, 0.f);
        movement.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        view.move(5.f, 0.f);
        movement.x += speed;
    }

    window.setView(view);

    return movement;
}
