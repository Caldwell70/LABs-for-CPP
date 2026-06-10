#pragma once

#include "bonus.h"

class RandomTrajectoryBonus : public Bonus
{
public:
    RandomTrajectoryBonus(float x, float y);

    void apply(Paddle& paddle, Ball& ball, bool& stickyMode, bool& extraBottom) override;
};