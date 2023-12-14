#pragma once

#include "Core/Engine.h"

struct Shooter {
	ECS_DECLARE_TYPE;

	float fireDelay{0.0f};
	float timeSinceLastShot{0.0f};
};
ECS_DEFINE_TYPE(Shooter);
