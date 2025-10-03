#pragma once
#include <Box2D/Box2D.h>

class Physics {
public:
    Physics();
    void step(float delta);

    b2World& get_world() { return world_; }

private:
    b2World world_;
};