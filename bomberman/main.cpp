#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "World.hpp"

class Bomberman
{
public:
    Bomberman()
        : window{sf::VideoMode(800, 600), "bomberman"}, world{window.getView()},
          board{window.getView()}, player{sf::Vector2f{20.f, 20.f}}
    {
        window.setVerticalSyncEnabled(true);
        player.setFillColor(sf::Color::Black);
    }

    void run()
    {
        sf::Clock frameClock;
        while (window.isOpen())
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
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape))
            {
                window.close();
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
        movePlayer(movementDirection * baseSpeed * bonusSpeed * deltaTime);
    }

    void movePlayer(const sf::Vector2f& transl)
    {
        if (sf::FloatRect{{0.f, 0.f},
                          window.getView().getSize() - sf::Vector2f{40.f, 40.f}}
            .contains(player.getPosition() + transl))
        {
            player.setPosition(player.getPosition() + transl);
        }
    }

    void render()
    {
        window.clear(sf::Color::Black);
        board.drawOn(window);
        world.draw(window);
        window.draw(player);
        window.display();
    }

    sf::RenderWindow window;
    lmg01::World world;
    lmg01::Board board;

    const float baseSpeed = 200.f;
    float bonusSpeed = 1.0f;
    sf::Vector2f movementDirection{0, 0};

    sf::RectangleShape player;
};

int main()
{
    Bomberman bomberman;
    bomberman.run();
}
