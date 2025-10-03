#include "SlingShot.h"

Slingshot::Slingshot(sf::Vector2f pos)
    :basePos_(pos), currentBird_(nullptr), dragging_(false), launched_(false)

{
    post_.setSize({10.f, 120.f});
    post_.setOrigin(post_.getSize().x / 2.f, 0.f);
    post_.setPosition(pos);
    post_.setFillColor(sf::Color(139,69,19));
}

void Slingshot::attach_bird(Bird* bird){
    currentBird_ = bird;
    launched_ = false;
    dragging_ = false;
    dragPos_ = basePos_;

    dragPos_ = post_.getPosition();
    currentBird_->shape().setPosition(dragPos_);
    if (currentBird_->body()) {
       
        b2Vec2 box2dPos(dragPos_.x / 30, dragPos_.y / 30);
        float angle = 0.0f; 
        currentBird_->body()->SetTransform(box2dPos, angle);
        b2Fixture* fixture =currentBird_->body()->GetFixtureList();
        fixture->SetSensor(true);
        currentBird_->body()->SetLinearVelocity(b2Vec2(0,0));
        currentBird_->body()->SetAngularVelocity(0);
        currentBird_->body()->SetType(b2_kinematicBody);
    }
}

void Slingshot::handle_event(const sf::Event& event, sf::RenderWindow& window){
    if(!currentBird_ || launched_) return;

    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
        sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

        if(currentBird_->shape().getGlobalBounds().contains(mousePos))
            dragging_ = true;
    }

    else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left ){
        if(dragging_){
            dragging_ = false;
            launched_ = true;

            sf::Vector2f direction = basePos_ - dragPos_; 
            float strength = 0.4f; 
            sf::Vector2f impulse = direction * strength;
            currentBird_->body()->SetType(b2_dynamicBody);
            currentBird_->launch(impulse);
            currentBird_ = nullptr;  

        }
    }

    else if(event.type == sf::Event::MouseMoved && dragging_){
        dragPos_ = window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});

        float maxDist = 80.f;
        sf::Vector2f diff =dragPos_ - basePos_;
        float dist = std::sqrt(diff.x*diff.x + diff.y*diff.y);
        if (dist > maxDist) {
            diff *= maxDist / dist;
            dragPos_ = basePos_ + diff;
        }
        currentBird_->body()->SetTransform({dragPos_.x / 30.f, dragPos_.y / 30.f}, 0.f);
    }
}

void Slingshot::update(float delta) {
    if (dragging_ && currentBird_) {
        currentBird_->shape().setPosition(dragPos_);
    }
}

void Slingshot::render(sf::RenderWindow& window) {
    window.draw(post_);
    if (currentBird_ && dragging_) {
        sf::Vertex line[] = { sf::Vertex(basePos_, sf::Color::Black), sf::Vertex(dragPos_, sf::Color::Black) };
        window.draw(line, 3, sf::Lines);
    }
}