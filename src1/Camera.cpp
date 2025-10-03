#include "Camera.h"

Camera::Camera(float mapWidth, float mapHeigt, sf::Vector2f viewSize)
 :mapWidth_(mapWidth), mapHeight_(mapHeigt), state_(State::Showmap)
 ,timer_(0.f), targetPos_(mapWidth / 2.f , mapHeigt / 2.f), targetZoom_(1.f), window(nullptr)
{
    view_.setSize(viewSize);
    view_.setCenter(targetPos_);
}

sf::Vector2f Camera::lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t){
    return a + t * (b - a);
}

void Camera::set_window(sf::RenderWindow* wnd){
    window = wnd;
}

void Camera::set_target(sf::Vector2f position){
    targetPos_ = position;
}

void Camera::follow_bird(sf::Vector2f birdPos){
    state_ = State::FollowBird;
    targetPos_ = birdPos;
    targetZoom_ = 0.9f;
    timer_ = 0.f;
}

void Camera::start_next_bird(sf::Vector2f birdPos){
    state_ = State::FocusBird;
    targetPos_ = birdPos;
    targetZoom_ = 0.9f;
    timer_ = 0.f;
}

void Camera::zoom_out(){
    state_ = State::ZoomOut;
    targetPos_ = {mapWidth_/2.f, 200};
    targetZoom_ = 1.5f;
    timer_ = 0.f;
}

void Camera::update(float delta){
    timer_ += delta;

    sf::Vector2f newCenter = lerp(view_.getCenter(), targetPos_, delta * 3.f);
    newCenter.x = std::clamp(newCenter.x, 0.f, mapWidth_);
    view_.setCenter(newCenter);

    float currentZoom = view_.getSize().x / 1024.f; 
    float newZoom = currentZoom + (targetZoom_ - currentZoom) * delta * 2.f;
    view_.setSize(1024.f * newZoom, 768.f * newZoom); 
}