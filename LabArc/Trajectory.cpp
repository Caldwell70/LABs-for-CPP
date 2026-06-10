#include "Trajectory.h"
#include "ball.h"

#include <random>
#include <cmath>

RandomTrajectoryBonus::RandomTrajectoryBonus(float x, float y)
{
    shape.setRadius(10.f);
    shape.setPosition({ x,y });
    shape.setFillColor(sf::Color::Blue);
}

void RandomTrajectoryBonus::apply(Paddle&, Ball& ball, bool&, bool&)
{
    static std::mt19937 rng(std::random_device{}());

    std::uniform_real_distribution<float>angleDist(30.f, 150.f);

    float speed =std::sqrt(ball.velocity.x * ball.velocity.x + ball.velocity.y * ball.velocity.y);

    float angle = angleDist(rng) * 3.1415926f / 180.f;

    ball.velocity.x = speed * std::cos(angle);

    ball.velocity.y = -speed * std::sin(angle);
}