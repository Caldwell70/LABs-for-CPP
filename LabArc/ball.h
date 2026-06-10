#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
public:
    sf::CircleShape shape;

    sf::Vector2f velocity;

    bool attached = true;

    Ball();

    void update(float dt);
};