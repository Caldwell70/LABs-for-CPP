#include "BigPaddle.h"
#include "paddle.h"

BiggerPaddleBonus::BiggerPaddleBonus(float x, float y)
{
    shape.setRadius(10.f);
    shape.setPosition({ x,y });
    shape.setFillColor(sf::Color::Green);
}

void BiggerPaddleBonus::apply(Paddle& paddle, Ball&, bool&, bool&)
{
    paddle.shape.setSize({
        paddle.shape.getSize().x + 40.f,
        20.f
        });
}