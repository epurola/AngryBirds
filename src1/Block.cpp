#include "Block.h"

Block::Block(b2World& world, sf::Vector2f pos, sf::Vector2f size, bool destroyable)
    : RectangleEntity(world, size, pos, true), destroyable_(destroyable), destroyed_(false)
{
   set_color(sf::Color(139, 69, 19)); // brown
}

bool Block::destroyed() const{
    return destroyed_;
}