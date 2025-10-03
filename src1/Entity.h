#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>


class Entity{
public:
    Entity(b2World& world, bool dynamic)
        : world_(world), dynamic_(dynamic) {}
    virtual ~Entity() {};

    virtual void update(float delta) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    b2Body* body() { return body_; }

    void set_active(bool b) { active_ = b; }
    bool active() const { return active_; }

protected:
    b2World& world_;
    b2Body* body_;
    bool dynamic_;
    float scale_ = 30.f;
    bool active_ = true;
};