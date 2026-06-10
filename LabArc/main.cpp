#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <optional>
#include <memory>

#include "ball.h"
#include "paddle.h"
#include "block.h"
#include "bonus.h"
#include "BonusFactory.h"

constexpr int WINDOW_WIDTH = 765;
constexpr int WINDOW_HEIGHT = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Arkanoid");

    window.setFramerateLimit(60);

    Paddle paddle;
    Ball ball;

    int score = 0;
    int defeats = 0;

    ball.shape.setPosition({
        paddle.shape.getPosition().x + 20.f,
        paddle.shape.getPosition().y - 25.f
    });

    std::vector<Block> blocks;
    std::vector<std::unique_ptr<Bonus>> bonuses;

    bool extraBottom = false;
    bool stickyMode = false;

    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            BlockType type;

            if (row == 0)
                type = BlockType::INDESTRUCTIBLE;
            else if (row == 1)
                type = BlockType::HEALTH;
            else if (row == 2)
                type = BlockType::BONUS;
            else if (row == 3)
                type = BlockType::SPEED;
            else
                type = BlockType::NORMAL;

            int hp = (type == BlockType::HEALTH) ? 3 : 1;

            blocks.emplace_back(10.f + col * 75.f, 50.f + row * 30.f, type, hp);
        }
    }

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>();

                if (key &&
                    key->code == sf::Keyboard::Key::Space)
                {
                    ball.attached = false;
                }
            }
        }

        paddle.update(dt);

        if (ball.attached)
        {
            ball.shape.setPosition({
                paddle.shape.getPosition().x + paddle.shape.getSize().x / 2.f - ball.shape.getRadius(),
                paddle.shape.getPosition().y - 25.f
                });
        }

        ball.update(dt);

        auto ballBounds = ball.shape.getGlobalBounds();

        if (ballBounds.position.x <= 0)
            ball.velocity.x *= -1;

        if (ballBounds.position.x + ballBounds.size.x >= WINDOW_WIDTH)
            ball.velocity.x *= -1;

        if (ballBounds.position.y <= 0)
            ball.velocity.y *= -1;

        if (ballBounds.position.y > WINDOW_HEIGHT)
        {
            if (extraBottom)
            {
                ball.velocity.y *= -1;
                extraBottom = false;
            }
            else
            {
                score -= 5;
                defeats++;

                ball.attached = true;

                ball.shape.setPosition({
                    paddle.shape.getPosition().x + paddle.shape.getSize().x / 2.f - ball.shape.getRadius(),
                    paddle.shape.getPosition().y - 25.f
                });

                ball.velocity = { 250.f,-250.f };
            }
        }

        if (ballBounds.findIntersection(paddle.shape.getGlobalBounds()))
        {
            ball.velocity.y = -std::abs(ball.velocity.y);

            if (stickyMode)
            {
                ball.attached = true;

                ball.shape.setPosition({
                    paddle.shape.getPosition().x + paddle.shape.getSize().x / 2.f - ball.shape.getRadius(),
                    paddle.shape.getPosition().y - 25.f
                    });

                stickyMode = false;
            }
        }

        for (auto& block : blocks)
        {
            if (!block.alive)
                continue;

            if (ballBounds.findIntersection(block.shape.getGlobalBounds()))
            {
                ball.velocity.y *= -1;

                float maxSpeed = 700.f;

                if (block.type == BlockType::SPEED)
                {
                    ball.velocity *= 1.2f;

                    float speed = std::sqrt(ball.velocity.x * ball.velocity.x + ball.velocity.y * ball.velocity.y);

                    if (speed > maxSpeed)
                    {
                        ball.velocity *= maxSpeed / speed;
                    }
                }

                if (block.type != BlockType::INDESTRUCTIBLE)
                {
                    score++;

                    bool destroyed = block.hit();

                    if (destroyed && block.type == BlockType::BONUS)
                        bonuses.push_back(BonusFactory::create(block.shape.getPosition().x, block.shape.getPosition().y));
                }

                break;
            }
        }

        for (auto& bonus : bonuses)
        {
            if (!bonus->active)
                continue;

            bonus->update(dt);

            if (bonus->shape.getGlobalBounds().findIntersection(paddle.shape.getGlobalBounds()))
            {
                bonus->active = false;

                bonus->apply(paddle, ball, stickyMode, extraBottom);
            }
        }

        window.setTitle("Arkanoid | Score: " + std::to_string(score) + " | Defeats: " + std::to_string(defeats));

        window.clear();

        for (auto& block : blocks)
        {
            if (block.alive || block.type == BlockType::INDESTRUCTIBLE)
                window.draw(block.shape);
        }

        for (auto& bonus : bonuses)
        {
            if (bonus->active)
                window.draw(bonus->shape);
        }

        window.draw(paddle.shape);
        window.draw(ball.shape);

        window.display();
    }

    return 0;
}