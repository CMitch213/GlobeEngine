#include "Soldier.h"
#include "Projectile.h"
#include "../Components/GameComponents.h"
#include "Utils/States.h"

Soldier::Soldier(ECS::World* world, const size_t id, const std::string picturePath, sf::Vector2f position) : 
	ECS::Entity(world, id)
{
	Engine& engine = Engine::GetInstance();
	engine.world = getWorld();
	this->id = id;

	entity = engine.world->create();

	entity->assign<Sprite2D>(picturePath);
	entity->assign<BoxCollider>();
	entity->assign<Tag>();
	entity->assign<Transform>(position.x, position.y, 0.03f, 0.03f, 0.0f, 0.05f);
	entity->assign<Shooter>();
	entity->get<Shooter>()->fireDelay = 500.0f;
	entity->assign<std::vector<Projectile*>>(std::vector<Projectile*>());
	
	entity->assign<CallbackEntity>(&Soldier::Fire);
}

void Soldier::Fire(ECS::Entity* entity)
{
	std::cout << "Fired!\n";
}
