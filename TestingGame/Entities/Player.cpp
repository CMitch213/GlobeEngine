#include "Player.h"

Player::Player(ECS::World* world, const size_t id, sf::Vector2f position) :
	Soldier(world, id, "../Debug/Pics/Soldier.png", position)
{
	this->world = world;
	this->id = id;

	entity->assign<InputController>();
	entity->get<Tag>()->AddTag("Player");
}
