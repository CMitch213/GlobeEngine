#pragma once
#include "Soldier.h"
class Player : public Soldier
{
public:
	Player() = default;
	Player(sf::Vector2f position);
	~Player() = default;
};

