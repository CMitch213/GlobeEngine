#pragma once
#include "../Core/Engine.h"

class RenderingSystem:public ECS::EntitySystem
{

	RenderingSystem() = default;
	~RenderingSystem() = default;
	void tick(ECS::World* world, float deltaTime) override;

};

