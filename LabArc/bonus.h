#pragma once

#include <SFML/Graphics.hpp>

class Ball;
class Paddle;

class Bonus
{
public:
    sf::CircleShape shape;

    bool active = true;

    virtual ~Bonus() = default;

    virtual void apply(Paddle& paddle, Ball& ball, bool& stickyMode, bool& extraBottom) = 0;

    virtual void update(float dt)
    {
        shape.move({ 0.f,250.f * dt });
    }
};