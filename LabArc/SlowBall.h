#pragma once

#include "bonus.h"

class SlowerBallBonus : public Bonus
{
public:
    SlowerBallBonus(float x, float y);

    void apply(Paddle& paddle, Ball& ball, bool& stickyMode, bool& extraBottom) override;
};