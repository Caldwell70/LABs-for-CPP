#pragma once

#include "bonus.h"

class StickyBonus : public Bonus
{
public:
    StickyBonus(float x, float y);

    void apply(Paddle& paddle, Ball& ball, bool& stickyMode, bool& extraBottom) override;
};