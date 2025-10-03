#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "RectangleEntity.h"

class Block : public RectangleEntity{

public:
    Block(b2World& world, sf::Vector2f pos, sf::Vector2f size, bool destroyable);
    bool destroyable() const;
    bool destroyed() const;

private:
    bool destroyable_;
    bool destroyed_;
};