#include "Sticky.h"

StickyBonus::StickyBonus(float x, float y)
{
    shape.setRadius(10.f);
    shape.setPosition({ x,y });
    shape.setFillColor(sf::Color::Magenta);
}

void StickyBonus::apply(Paddle&, Ball&, bool& stickyMode, bool&)
{
    stickyMode = true;
}