#pragma once
#include "../Core/Engine.h"

class MainCamera
{
public:
	sf::View cameraView;
	MainCamera() = default;
	MainCamera(sf::Vector2f pivot);
	void Update(ECS::World* world, float deltaTime, sf::RenderWindow* window);
	~MainCamera() = default;
};

