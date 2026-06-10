#include "SlowBall.h"
#include "ball.h"

SlowerBallBonus::SlowerBallBonus(float x, float y)
{
    shape.setRadius(10.f);
    shape.setPosition({ x,y });
    shape.setFillColor(sf::Color::Cyan);
}

void SlowerBallBonus::apply(Paddle&, Ball& ball, bool&, bool&)
{
    ball.velocity *= 0.7f;
}