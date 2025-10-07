#pragma once
#include <memory>
#include <vector>
#include "Level.h"
#include "Physics.h"
#include "Layout.h"

class Game {

public:
    Game();
    void start();

private:
    void handle_input();
    void update(float delta);
    void render();

    Layout layout_; // Experiment to remove magic numbers probably dont need it.

    sf::RenderWindow window_;

    //The 3 levels that are required should be stord here.
    std::vector<std::unique_ptr<Level>> levels_;
    int currentlevel_;
    int score_;
    bool running_;
    // PThis is the physics engine (Box2D older version)
    Physics physics_;
    //Camera for view management because the view was supposed to follow the bird.
    Camera camera_;

    
};