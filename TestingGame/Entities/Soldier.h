#pragma once

#include "Core/Engine.h"

typedef void(*CallbackEntity)(ECS::Entity*);

class Projectile;

class Soldier : public ECS::Entity
{
protected:
	size_t id;
	ECS::Entity* entity {nullptr};
	Projectile* projectile{ nullptr };
	sf::Vector2f speed;

public:
	Soldier() = default;
	Soldier(ECS::World* world, const size_t id, std::string picturePath, sf::Vector2f position);
	~Soldier() = default;

private:
	static void Fire(ECS::Entity* entity);
};

