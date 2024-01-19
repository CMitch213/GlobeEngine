#include "Enemy.h"

Enemy::Enemy(ECS::World* world, const size_t id, sf::Vector2f position) :
	Soldier(world, id, "../Debug/Pics/Enemy.png", position)
{
	this->world = world;
	this->id = id;

	entity->get<Tag>()->AddTag("Enemy");
	entity->get<Transform>()->Normalize(sf::Vector2f(1.0f, 1.0f));
}
