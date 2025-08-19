#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <iostream>

class Food
{
    sf::RectangleShape shape = sf::RectangleShape({10, 10});
    float position[2] = {0, 0};
    sf::Clock clock;
    public:
    Food()
    {
        shape.setFillColor(sf::Color::Green);
        position[0] = (10+std::rand())%591;
        position[1] = (10+std::rand())%591;
        shape.setPosition({position[0], position[1]});
    }

    void CheckCollision(Player& player)
    {
        if (shape.getGlobalBounds().findIntersection(player.shape.getGlobalBounds()))
        {
            Eaten(player);
        }
    }
    void Eaten(Player& player)
    {
        std::srand(clock.getElapsedTime().asSeconds());
        position[0] = (10+std::rand())%591;
        position[1] = (10+std::rand())%591;
        shape.setPosition({position[0], position[1]});
        player.AddCell();
    }

    void drawTo(sf::RenderWindow& window)
    {
        window.draw(shape);
    }
};