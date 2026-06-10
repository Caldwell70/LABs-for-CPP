#include "BonusFactory.h"
#include "BombBonus.h"
#include "RecolorBonus.h"

#include <random>

extern std::mt19937 rng;

std::unique_ptr<Bonus>
BonusFactory::create()
{
    std::uniform_int_distribution<int> dist(0, 1);

    if (dist(rng))
    {
        return std::make_unique<RecolorBonus>();
    }

    return std::make_unique<BombBonus>();
}