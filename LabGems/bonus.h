#pragma once

class Board;

class Bonus
{
public:

    virtual ~Bonus() = default;

    virtual void apply(
        Board& board,
        int row,
        int col,
        int sourceColor) = 0;
};