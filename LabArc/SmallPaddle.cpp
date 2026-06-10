#include "SmallPaddle.h"
#include "paddle.h"

SmallerPaddleBonus::SmallerPaddleBonus(float x, float y)
{
    shape.setRadius(10.f);
    shape.setPosition({ x,y });
    shape.setFillColor(sf::Color::Red);
}

void SmallerPaddleBonus::apply(Paddle& paddle, Ball&, bool&, bool&)
{
    paddle.shape.setSize({
        std::max(
            50.f,
            paddle.shape.getSize().x - 40.f),
        20.f
        });
}