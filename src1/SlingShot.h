#pragma once
#include "Bird.h"

class Slingshot{
public:
    Slingshot(sf::Vector2f pos);

    void attach_bird(Bird* bird);
    void handle_event(const sf::Event& event, sf::RenderWindow& window);

    void update(float delta);
    void render(sf::RenderWindow& window);

    bool launched() const { return launched_; }

private:
    bool launched_;
    bool dragging_;

    sf::Vector2f basePos_;
    Bird* currentBird_;
    sf::Vector2f dragPos_;
    sf::RectangleShape post_;

};