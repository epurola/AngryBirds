#include "Bird.h"

Bird::Bird(b2World& world, sf::Vector2f pos,const sf::Texture* texture, float radius)
    : CircleEntity(world, radius, pos, true), launched_(false), specialused_(false)
{
    if (texture)
        set_texture(texture);
}

void Bird::launch(const sf::Vector2f& impulse)
{
    if (launched_) return;

    b2Vec2 boxImpulse(impulse.x, impulse.y);
    body_->ApplyLinearImpulseToCenter(boxImpulse, true);

    launched_ = true;
    b2Fixture* fixture = body()->GetFixtureList();
    fixture->SetSensor(false);
}


void Bird::special()
{
    if (specialused_) return;

//add a speed boost in current direction
    b2Vec2 vel = body_->GetLinearVelocity();
    vel *= 1.5f;
    body_->SetLinearVelocity(vel);

    specialused_ = true;
}
