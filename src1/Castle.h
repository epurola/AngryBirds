#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Block.h"


class Castle{
public:
    Castle() = default;
    void add_block(const Block& block);
    void update(float delta);
    void render(sf::RenderWindow& block);

private:
    std::vector<Block> blocks_;
};