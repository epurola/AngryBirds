#pragma once
#include "Entity.h"
class PolygonEntity : public Entity {
public:
    PolygonEntity(b2World& world, const std::vector<sf::Vector2f>& vertices, sf::Vector2f pos, bool dynamic);

    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    sf::ConvexShape shape_;
};

