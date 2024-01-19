#pragma once
#include "Core/Engine.h"
class GameMovementSystem : public ECS::EntitySystem
{
public:
	float timer{ 0.0f };
	
	GameMovementSystem() = default;
	~GameMovementSystem() = default;

	void tick(ECS::World* world, float deltaTime) override;
};

