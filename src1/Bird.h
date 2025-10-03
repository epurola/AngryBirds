#pragma once
#include <SFML/graphics.hpp>
#include "CircleEntity.h"

class Bird : public CircleEntity{

public: 
    Bird(b2World& world, sf::Vector2f pos, const sf::Texture* texture, float radius = 20.f );
    void launch(const sf::Vector2f& impulse);
    void special();

    bool launched() const { return launched_; }


private:
    bool launched_;
    bool specialused_;

};