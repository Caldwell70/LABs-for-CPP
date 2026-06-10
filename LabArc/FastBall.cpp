#include "FastBall.h"
#include "ball.h"

FasterBallBonus::FasterBallBonus(float x, float y)
{
    shape.setRadius(10.f);
    shape.setPosition({ x,y });
    shape.setFillColor(sf::Color::Yellow);
}

void FasterBallBonus::apply(Paddle&, Ball& ball, bool&, bool&)
{
    ball.velocity *= 1.3f;
}