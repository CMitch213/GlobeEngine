#include "Player.h"

Player::Player(sf::Vector2f position) : Soldier("../Debug/Pics/Soldier.png", position)
{
	entity->assign<InputController>();
	entity->get<Tag>()->AddTag("Player");
}
