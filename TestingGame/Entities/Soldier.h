#pragma once
#include "Entity.h"
class Soldier : public Entity
{
public:
	Soldier() = default;
	Soldier(std::string picturePath, sf::Vector2f position);
	~Soldier() = default;

private:
	void Fire(ECS::Entity* entity);
};

