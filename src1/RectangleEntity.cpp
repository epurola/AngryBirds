#include "RectangleEntity.h"

RectangleEntity::RectangleEntity(b2World &world, sf::Vector2f size, sf::Vector2f pos, bool dynamic)
    : Entity(world, dynamic)
{
    shape_.setSize(size);
    shape_.setOrigin(size.x / 2.f, size.y / 2.f);
    shape_.setPosition(pos);
    shape_.setFillColor(sf::Color::White);

    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x / 30.f, pos.y / 30.f); 
    bodyDef.type = dynamic ? b2_dynamicBody : b2_staticBody;
    body_ = world.CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox((size.x / 2.f) / 30.f, (size.y / 2.f) / 30.f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = dynamic ? 1.f : 0.f;
    fixtureDef.friction = 0.5f;
    body_->CreateFixture(&fixtureDef);
}

void RectangleEntity::update(float delta)
{
    b2Vec2 pos = body_->GetPosition();
    float angle = body_->GetAngle();

    shape_.setPosition(pos.x * 30.f, pos.y * 30.f); // meters -> pixels
    shape_.setRotation(angle * 180.f / b2_pi); // radians -> degrees
}

void RectangleEntity::render(sf::RenderWindow& window)
{
    window.draw(shape_);
}