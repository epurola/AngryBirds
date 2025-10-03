#pragma once
#include <string>
#include <vector>
#include "Bird.h"
#include "Castle.h"
#include "Enemy.h"
#include "Physics.h"
#include "RectangleEntity.h"
#include "SlingShot.h"
#include "Camera.h"
#include "Layout.h"

class Level{

public:
    Level(b2World& world, Physics& physics, Layout& layout, const std::string& file);
    ~Level(); // remeber to clean up here !! 
    void load(const std::string& file);

    void update(float delta, Camera& camera);
    void render(sf::RenderWindow& window, Camera& camera);

    bool completed() const;

    void handle_event(const sf::Event& event, sf::RenderWindow& window, Camera& camera);

private:
    Physics& physics_;
    Layout& layout_;
    std::vector<Bird> birds_;
    Castle castle_;
    std::vector<Enemy> enemies_;

    int currentBird_;
    size_t flyingBirdIndex_;
    std::unique_ptr<RectangleEntity> ground_;
    Slingshot slingshot_;

    sf::Texture birdTexture_;
    sf::Texture birdTexture2_;
    sf::Texture pigTexture_;
    sf::Texture bg_;
    sf::Sprite bgSprite_;
};