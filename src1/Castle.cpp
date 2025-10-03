#include "Castle.h"

void Castle::add_block(const Block &block)
{
    blocks_.push_back(block);
}

void Castle::update(float delta){
    for (auto& block : blocks_)
        block.update(delta); 
}

void Castle::render(sf::RenderWindow& window){
    for(auto& block : blocks_)
        block.render(window);
}