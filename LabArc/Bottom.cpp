#include "Bottom.h"

ExtraBottomBonus::ExtraBottomBonus(float x, float y)
{
    shape.setRadius(10.f);
    shape.setPosition({ x,y });
    shape.setFillColor(sf::Color::White);
}

void ExtraBottomBonus::apply(Paddle&, Ball&, bool&, bool& extraBottom)
{
    extraBottom = true;
}