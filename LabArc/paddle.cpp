#include "paddle.h"

Paddle::Paddle()
{
    shape.setSize({ 120.f,20.f });

    shape.setPosition({ 325.f,550.f });
}

void Paddle::update(float dt)
{
    float speed = 500.f;

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::A))
    {
        shape.move({ -speed * dt, 0 });
    }

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::D))
    {
        shape.move({ speed * dt, 0 });
    }

    if (shape.getPosition().x < 0)
        shape.setPosition({
            0,
            shape.getPosition().y
            });

    if (shape.getPosition().x +
        shape.getSize().x > 765)
    {
        shape.setPosition({
            765 - shape.getSize().x,
            shape.getPosition().y
            });
    }
}