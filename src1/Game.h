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

    Layout layout_;

    sf::RenderWindow window_;

    std::vector<std::unique_ptr<Level>> levels_;
    int currentlevel_;
    int score_;
    bool running_;
    Physics physics_;
    Camera camera_;

    
};