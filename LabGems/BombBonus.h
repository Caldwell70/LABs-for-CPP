#pragma once

#include "bonus.h"

class BombBonus : public Bonus
{
public:
    void apply(Board& board, int row, int col, int sourceColor) override;
};