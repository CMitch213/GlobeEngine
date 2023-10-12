#pragma once
#include "../Core/Engine.h"
class MovementSystem : public ECS::EntitySystem
{
public:
	MovementSystem() = default;
	~MovementSystem() = default;

	void tick(ECS::World* world, float deltaTime) override;
};

