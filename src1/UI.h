#pragma once
#include <SFML/Graphics.hpp>

class UI {
public:
    UI();
    void render(sf::RenderWindow& window, int score, int birdsLeft, int enemiesLeft);
private:
    sf::Font font_;
    sf::Text scoreText_;
    sf::Text birdstext_;
    sf::Text enemiesText_;
};