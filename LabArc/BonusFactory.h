#pragma once

#include <memory>

class Bonus;

class BonusFactory
{
public:
    static std::unique_ptr<Bonus>create(float x, float y);
};