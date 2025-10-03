#pragma once
#include "Entity.h"

class CircleEntity : public Entity {
public:
    CircleEntity(b2World& world, float radius, sf::Vector2f pos, bool dynamic);

    void update(float delta) override;
    void render(sf::RenderWindow& window) override;
    void set_color(sf::Color color) { shape_.setFillColor(color); }
    sf::CircleShape& shape() { return shape_; }
    void set_texture(const sf::Texture* texture) { shape_.setTexture(texture); }

protected:
    sf::CircleShape shape_;
};
