#include "Game.h"

Game::Game() : currentlevel_(0), score_(0), running_(true),
window_(sf::VideoMode(layout_.windowWidth, layout_.windowHeight), "Angry Birds"), physics_(), 
camera_(layout_.windowWidth, layout_.windowHeight, { layout_.windowWidth, layout_.windowHeight })
{
    // Limit frame rate to 60 FPS for consistent timing
    window_.setFramerateLimit(60);
    // Load first level into the levels vector
    levels_.push_back(std::make_unique<Level>(physics_.get_world(), physics_, layout_, "levels/level1.txt")); 
    //Zoom out effect at the start of the game
    camera_.zoom_out();
}

// This starts the main game loop
void Game::start(){
    sf::Clock clock;

    while(running_){
        float delta = clock.restart().asSeconds(); // Time since last frame
        handle_input();
        update(delta);
        render();
    }
}

// Handle all player input & window events using sf::Events
void Game::handle_input(){
    sf::Event event;
    while(window_.pollEvent(event)){
        switch (event.type)
        {
        case sf::Event::Closed:
            window_.close();
            break;
        
        default:
            break;
        }

        // Forward event handling to the current level
        if (currentlevel_ < levels_.size()) {
            levels_[currentlevel_]->handle_event(event, window_, camera_);
        }
    }
}

void Game::render(){
    window_.clear(sf::Color::Cyan);
    window_.setView(camera_.get_view());

    if(currentlevel_ < levels_.size()){
        levels_[currentlevel_]->render(window_, camera_);
    }

    window_.display();
}

void Game::update(float delta){
    if(currentlevel_ < levels_.size()){
        levels_[currentlevel_]->update(delta, camera_);
    }
}