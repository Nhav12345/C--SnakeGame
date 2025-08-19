#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>


class PlayerCell
{
    float position[2];
    sf::RectangleShape shape = sf::RectangleShape({10, 10});
    public:
    float lastPosition[2];
    bool isAfterHead = false;
    PlayerCell(bool isAfterHead, float pos[2])
    {
        this->position[0] = pos[0]; this->position[1] = pos[1];
        this->isAfterHead = isAfterHead;
    }
    void MoveTo(float newPos[2])
    {
        lastPosition[0] = position[0]; lastPosition[1] = position[1];
        position[0] = newPos[0]; position[1] = newPos[1];
    }
    void update()
    {
        shape.setPosition({position[0], position[1]});
    }
    void drawTo(sf::RenderWindow& window)
    {
        window.draw(shape);
    }
};

class Player
{
    float velocity[2] = {0, 0};
    float position[2] = {0, 0};
    float lastPosition[2] = {0, 0};
    float speed = 10;
    sf::Clock clock;

    std::vector<PlayerCell> cells;

    public:
    sf::RectangleShape shape = sf::RectangleShape({10, 10});
    double secondDelay = 0.03;
    float* GetPos()
    {
        return position;
    }

    float* GetVelocity()
    {
        return velocity;
    }

    void Move(float direction[2])
    {
        velocity[0] = direction[0]*speed;
        velocity[1] = direction[1]*speed;
    }

    void HandleKeys()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            float mvmt[2] = {-1, 0};
            Move(mvmt);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            float mvmt[2] = {1, 0};
            Move(mvmt);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            float mvmt[2] = {0, -1};
            Move(mvmt);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            float mvmt[2] = {0, 1};
            Move(mvmt);
        }
    }

    void update()
    {
        HandleKeys();
        if (clock.getElapsedTime().asSeconds() >= secondDelay)
        {
            lastPosition[0] = position[0]; lastPosition[1] = position[1];
            position[0]+=velocity[0];
            position[1]+=velocity[1];
            shape.setPosition({position[0], position[1]});
        }
    }

    void updateCells()
    {
        if (clock.getElapsedTime().asSeconds() >= secondDelay)
        {
            for (int i = 0; i < cells.size(); i++)
            {
                if (cells[i].isAfterHead)
                {
                    cells[i].MoveTo(lastPosition);
                }
                else
                {
                    cells[i].MoveTo(cells[i-1].lastPosition);
                }
                cells[i].update();
            }
            clock.restart();
        }
    }

    void drawTo(sf::RenderWindow& window)
    {
        window.draw(shape);
        for (int i = 0; i<cells.size(); i++)
        {
            cells[i].drawTo(window);
        }
    }

    void AddCell()
    {
        if (cells.size() < 1)
        {
            PlayerCell cell = PlayerCell(true, lastPosition);
            cells.push_back(cell);
        }
        else
        {
            PlayerCell cell = PlayerCell(false, cells[cells.size()-1].lastPosition);
            cells.push_back(cell);
        }
    }

    Player(sf::RenderWindow& window)
    {
        window.draw(shape);
    }
};
