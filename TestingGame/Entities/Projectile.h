#pragma once
#include "Soldier.h"

class Projectile : ECS::Entity
{
protected:
	size_t id;
	ECS::Entity* entity{ nullptr };

public:
	Projectile() = default;
	Projectile(ECS::World* world, const size_t id, /*Soldier& shooter, const std::string picturePath, */ sf::Vector2f position, float angle, float speed);
	~Projectile();
};

