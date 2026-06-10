#pragma once

#include "bonus.h"

class FasterBallBonus : public Bonus
{
public:
    FasterBallBonus(float x, float y);

    void apply(Paddle& paddle, Ball& ball, bool& stickyMode, bool& extraBottom) override;
};