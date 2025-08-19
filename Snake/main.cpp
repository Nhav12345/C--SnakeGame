#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "App.hpp"
#include "Food.hpp"
#include <iostream>

int main()
{
    App app = App();
    Player player = Player(app.window);
    Food food = Food();
    sf::Clock clock;
    while (app.window.isOpen())
    {
        float startT = clock.restart().asSeconds();
        
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = app.window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                app.window.close();
        }

        // clear the window with black color
        app.window.clear(sf::Color::Black);
        player.update();

        food.CheckCollision(player);
        player.updateCells();

        food.drawTo(app.window);
        player.drawTo(app.window);

        app.EndFrame();
        float fps = 1.0/clock.restart().asSeconds();
        std::cout << "Framerate : " << fps << std::endl;
    }
}