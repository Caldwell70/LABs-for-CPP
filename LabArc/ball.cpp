#include "ball.h"

Ball::Ball()
{
    shape.setRadius(10.f);

    velocity = { 250.f,-250.f };
}

void Ball::update(float dt)
{
    if (!attached)
        shape.move(velocity * dt);
}