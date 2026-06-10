#pragma once

#include "bonus.h"

class BiggerPaddleBonus : public Bonus
{
public:
    BiggerPaddleBonus(float x, float y);

    void apply(Paddle& paddle, Ball& ball, bool& stickyMode, bool& extraBottom) override;
};