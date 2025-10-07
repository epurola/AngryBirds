#include "Physics.h"

Physics::Physics() : world_(b2Vec2(0.0f, 9.8f))
{
    world_.SetContactListener(&contactListener_);
}

void Physics::step(float delta)
{
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    world_.Step(delta, velocityIterations, positionIterations);
}
