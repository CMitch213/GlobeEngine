#pragma once
#include "../Core/Engine.h"
class InputSystem : public ECS::EntitySystem
{
private:
	sf::RenderWindow* window;

public:
	InputSystem(sf::RenderWindow* window);
	~InputSystem() = default;
	void tick(ECS::World* world, float deltaTime)override;
	void GetKeyEvents(ECS::World* world);
};

