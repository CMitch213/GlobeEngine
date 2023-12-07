#include "Soldier.h"

Soldier::Soldier(std::string picturePath, sf::Vector2f position)
{
	Engine& engine = Engine::GetInstance();
	entity = engine.world->create();
	entity->assign<Sprite2D>(picturePath);
	entity->assign<BoxCollider>();
	entity->assign<Tag>();
	entity->assign<Transform>(position.x, position.y, 0.03f, 0.03f, 0.0f, 0.05f);
	
}

void Soldier::Fire(ECS::Entity* entity)
{

}
