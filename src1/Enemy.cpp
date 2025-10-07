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
    pendingDestroy_ = true;
    std::cout << "Enemy scheduled for destruction\n";
      // Currently they die if speed is enough so one of them dies instantly since it is falling
}

void Enemy::update(float delta)
{
    if (!alive_) {
        if (pendingDestroy_) {
            world_.DestroyBody(body_);
            pendingDestroy_ = false;
        }
    }
    else {
        CircleEntity::update(delta);
    }
}

void Enemy::render(sf::RenderWindow& window)
{
    if (!alive_) return;

    window.draw(shape_);
}
