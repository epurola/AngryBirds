#include "Enemy.h"

Enemy::Enemy(b2World &world, sf::Vector2f pos, const sf::Texture* texture, float radius)
    : CircleEntity(world, radius, pos, true), alive_(true), radius_(radius)
{
    if (texture)
        set_texture(texture);
}

bool Enemy::alive() const
{
    return false;
}

void Enemy::kill()
{
    if (!alive_) return;
     
    alive_ = false;
    active_ = false;
    world_.DestroyBody(body_); // Currently they die if speed is enough so one of them dies instantly since it is falling
}

void Enemy::update(float delta)
{
    if (!alive_) {
    
        float t = deathTimer_.getElapsedTime().asSeconds();
        float scale = 1.f + t * 2.f; 
        shape_.setScale(scale, scale);
        shape_.setFillColor(sf::Color(255, 255, 255, std::max(0, int(255 * (1.f - t)))));

        if (t > 0.5f) {
            set_active(false); 
        }
    }
    else {
   
        CircleEntity::update(delta);
    }
}
