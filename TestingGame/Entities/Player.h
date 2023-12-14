#pragma once
#include "Soldier.h"
class Player : public Soldier
{
public:
	ECS::World* world {nullptr};

	Player() = default;
	Player(ECS::World* world, const size_t id, sf::Vector2f position);
	~Player() = default;
};

