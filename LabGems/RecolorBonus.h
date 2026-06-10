#pragma once

#include "bonus.h"

class RecolorBonus : public Bonus
{
public:
    void apply(Board& board, int row, int col, int sourceColor) override;
};