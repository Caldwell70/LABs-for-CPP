#pragma once

#include <SFML/Graphics.hpp>

enum class BlockType
{
    NORMAL,
    INDESTRUCTIBLE,
    BONUS,
    SPEED,
    HEALTH
};

class Block
{
public:
    sf::RectangleShape shape;

    BlockType type;

    int health;

    bool alive;

    Block(float x, float y, BlockType t, int hp = 1);

    bool hit();
};