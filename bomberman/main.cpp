#include <SFML/Graphics.hpp>

#include "World.hpp"

class Bomberman
{
public:
    Bomberman()
        : mainWindow{sf::VideoMode(800, 600), "bomberman"},
          world{mainWindow.getView()}
    {
        mainWindow.setVerticalSyncEnabled(true);
    }

    void run()
    {
        sf::Clock frameClock;
        while (mainWindow.isOpen())
        {
            sf::Time frameTick = frameClock.restart();

            updateInput();
            updateMovement(frameTick.asSeconds());
            render();
        }
    }

private:
    void updateInput()
    {
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape))
            {
                mainWindow.close();
            }
        }
        updatePlayerInput();
    }

    void updatePlayerInput()
    {
        movementDirection = sf::Vector2f{0, 0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            movementDirection.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            movementDirection.y = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            movementDirection.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            movementDirection.x = 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            bonusSpeed = 0.5f;
        }
        else
        {
            bonusSpeed = 1.0f;
        }
    }

    void updateMovement(float deltaTime)
    {
        world.movePlayer(movementDirection * baseSpeed * bonusSpeed *
                         deltaTime);
    }

    void render()
    {
        mainWindow.clear(sf::Color::Black);
        world.draw(mainWindow);
        mainWindow.display();
    }

    sf::RenderWindow mainWindow;
    lmg01::World world;

    const float baseSpeed = 200.f;
    float bonusSpeed = 1.0f;
    sf::Vector2f movementDirection{0, 0};
};

int main()
{
    Bomberman bomberman;
    bomberman.run();
}
