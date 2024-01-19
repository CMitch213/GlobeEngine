#pragma once

#include "Soldier.h"

class Enemy : public Soldier
{
public:
	ECS::World* world{ nullptr };

	Enemy() = default;
	Enemy(ECS::World* world, const size_t id, sf::Vector2f position);
	~Enemy() = default;
};

