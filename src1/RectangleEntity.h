#pragma once
#include "Entity.h"

class RectangleEntity : public Entity{
public:
    RectangleEntity(b2World& world, sf::Vector2f size, sf::Vector2f pos, bool dynamic);

    void update(float delta) override;
    void render(sf::RenderWindow& window) override;

    sf::RectangleShape& shape() { return shape_; }
    void set_color(sf::Color color) { shape_.setFillColor(color); }

private:
    sf::RectangleShape shape_;

};