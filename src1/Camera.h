#pragma once
#include <SFML/Graphics.hpp>

class Camera{
public:
    enum class State { Showmap, FocusBird, FollowBird, ZoomOut};

    Camera(float mapWidth, float mapHeigt, sf::Vector2f viewSize);

    void update(float delta);
    void set_target(sf::Vector2f position);
    void follow_bird(sf::Vector2f birdPos);
    void start_next_bird(sf::Vector2f birdPos);
    void zoom_out();

    void set_window(sf::RenderWindow* window);
    sf::View& get_view() { return view_;}

private:
    sf::View view_;
    State state_;
    sf::Vector2f targetPos_;
    float targetZoom_;
    float mapWidth_;
    float mapHeight_;
    float timer_;


    sf::RenderWindow* window;
    sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t);
};