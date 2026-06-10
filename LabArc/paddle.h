#pragma once

#include <SFML/Graphics.hpp>

class Paddle
{
public:
    sf::RectangleShape shape;

    Paddle();

    void update(float dt);
};