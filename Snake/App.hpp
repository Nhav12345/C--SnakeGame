#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class App
{
    public:
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({600, 600}), "Snake");
    sf::RenderWindow& GetWindow()
    {
        return window;
    }
    void EndFrame()
    {
        // end the current frame
        window.display();
    }
    App()
    {
        window.setFramerateLimit(60);
    }
};