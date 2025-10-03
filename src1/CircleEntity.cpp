#include "CircleEntity.h"
#include <cmath>

CircleEntity::CircleEntity(b2World& world, float radius, sf::Vector2f pos, bool dynamic)
    : Entity(world, dynamic) 
{
    shape_.setRadius(radius);
    shape_.setOrigin(radius, radius); 
    shape_.setPosition(pos);
    shape_.setFillColor(sf::Color::White);

    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x / scale_, pos.y / scale_);
    bodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
    body_ = world.CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = radius / scale_;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = dynamic ? 1.f : 0.f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.3f; 
    fixtureDef.isSensor = false;
    body_->CreateFixture(&fixtureDef);

    body_->SetAngularDamping(2.0f);
}

void CircleEntity::update(float delta)
{
    b2Vec2 pos = body_->GetPosition();
    float angle = body_->GetAngle();

    shape_.setPosition(pos.x * scale_, pos.y * scale_);
    shape_.setRotation(angle * 180.f / b2_pi);
}

void CircleEntity::render(sf::RenderWindow& window)
{
    window.draw(shape_);
}
