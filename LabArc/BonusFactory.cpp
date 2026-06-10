#include "BonusFactory.h"

#include "BigPaddle.h"
#include "SmallPaddle.h"
#include "FastBall.h"
#include "SlowBall.h"
#include "Sticky.h"
#include "Bottom.h"
#include "Trajectory.h"

#include <random>

std::unique_ptr<Bonus>BonusFactory::create(float x, float y)
{
    static std::mt19937 rng(std::random_device{}());

    std::uniform_int_distribution<int>dist(0, 6);

    switch (dist(rng))
    {
    case 0:
        return std::make_unique<BiggerPaddleBonus>(x, y);

    case 1:
        return std::make_unique<SmallerPaddleBonus>(x, y);

    case 2:
        return std::make_unique<FasterBallBonus>(x, y);

    case 3:
        return std::make_unique<SlowerBallBonus>(x, y);

    case 4:
        return std::make_unique<StickyBonus>(x, y);

    case 5:
        return std::make_unique<ExtraBottomBonus>(x, y);

    default:
        return std::make_unique<RandomTrajectoryBonus>(x, y);
    }
}