#pragma once

#include "bonus.h"

class SmallerPaddleBonus : public Bonus
{
public:
    SmallerPaddleBonus(float x, float y);

    void apply(Paddle& paddle, Ball& ball, bool& stickyMode, bool& extraBottom) override;
};