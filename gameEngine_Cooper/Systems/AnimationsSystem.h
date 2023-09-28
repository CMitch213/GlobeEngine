#pragma once
#include "../Core/Engine.h"

class AnimationsSystem: public ECS::EntitySystem
{
public:
	AnimationsSystem() = default;
	~AnimationsSystem() = default;

private:
	void tick(ECS::World* world, float deltaTime) override;
};

