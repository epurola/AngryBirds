#pragma once
#include <SFML/Graphics.hpp>
#include "CircleEntity.h"

class Enemy : public CircleEntity{
public:
    Enemy(b2World& world, sf::Vector2f pos, const sf::Texture* texture, float radius = 20.f);

    bool alive() const;
    void kill();

    void update(float delta) override;


private:
    bool alive_;
    float radius_;
    const float SCALE_ = 30.f;
    sf::Clock deathTimer_;
};