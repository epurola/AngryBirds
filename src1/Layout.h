#pragma once
#include <SFML/System/Vector2.hpp>

struct Layout {
	float windowWidth = 1024.f;
	float windowHeight = 768.f;

	float groundHeight = 90.f;
	float slingshotOffsetX = 150.f;
	float slingshotOffsetY = 25.f;

	float scale = 30.f;

	sf::Vector2f groundPosition() const {
		return { windowWidth / 2.f, windowHeight - groundHeight };
	}

	sf::Vector2f slingshotPosition() const {
		return{ slingshotOffsetX, windowHeight - groundHeight - slingshotOffsetY };
	}

	float screenCenterY() const {
		return windowHeight / 2.f;
	}
};