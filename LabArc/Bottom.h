#pragma once

#include "bonus.h"

class ExtraBottomBonus : public Bonus
{
public:
    ExtraBottomBonus(float x, float y);

    void apply(Paddle& paddle, Ball& ball, bool& stickyMode, bool& extraBottom) override;
};