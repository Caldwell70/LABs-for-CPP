#include "block.h"

Block::Block(float x, float y, BlockType t, int hp)
{
    shape.setSize({ 70.f,25.f });
    shape.setPosition({ x,y });

    type = t;
    health = hp;
    alive = true;

    switch (type)
    {
    case BlockType::NORMAL:
        shape.setFillColor(sf::Color::Green);
        break;

    case BlockType::INDESTRUCTIBLE:
        shape.setFillColor(sf::Color(120, 120, 120));
        break;

    case BlockType::BONUS:
        shape.setFillColor(sf::Color::Yellow);
        break;

    case BlockType::SPEED:
        shape.setFillColor(sf::Color::Red);
        break;

    case BlockType::HEALTH:
        shape.setFillColor(sf::Color::Blue);
        break;
    }
}

bool Block::hit()
{
    if (type == BlockType::INDESTRUCTIBLE)
        return false;

    health--;

    if (health <= 0)
    {
        alive = false;
        return true;
    }

    return false;
}