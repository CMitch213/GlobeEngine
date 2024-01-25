#include "Soldier.h"
#include "Projectile.h"
#include "../Components/GameComponents.h"
#include "Utils/States.h"
#include <cmath>

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
	entity->assign<Transform>(sf::Vector2f(position.x, position.y), sf::Vector2f(speed.x, speed.y), 0.1f, 0.0f, 0.05f);
	entity->assign<Shooter>();
	entity->get<Shooter>()->fireDelay = 500.0f;
	entity->assign<std::vector<Projectile*>>(std::vector<Projectile*>());
	
	entity->assign<CallbackEntity>(&Soldier::Fire);
}

void Soldier::Fire(ECS::Entity* entity)
{
	std::cout << "Fired!\n";
	const ECS::ComponentHandle<Sprite2D> sprite = entity->get<Sprite2D>();
	const ECS::ComponentHandle<Transform> transform = entity->get<Transform>();
	const ECS::ComponentHandle<std::vector<Projectile*>> projectiles = entity->get<std::vector<Projectile*>>();

	for (size_t i = projectiles->size(); i >= 20; --i) {
		//Create projectiles ofr list
		Projectile* projectileElement = projectiles->at(0);
		//Delete first projectile in list
		projectiles->erase(projectiles->begin());
		//Delete the pointer
		delete projectileElement;
	}
	const Engine& engine = Engine::GetInstance();
	const size_t id = entity->getEntityId();

	const float thrust = std::fabs((entity->get<Transform>()->speed.x * 3.0f) + (entity->get<Transform>()->speed.y * 3.0f)) / 2.0f + 0.1f;

	//Create projectiles upon firing start from first
	const auto firedProjectile = new Projectile(engine.world, id, sf::Vector2f(transform->position.x, transform->position.y),
		sprite->picture.getRotation()/* - 90.0f*/, thrust);

	//Remove projectile from list
	projectiles->push_back(firedProjectile);

	//TO DO: FIX FIX FORCEFIELD GLITCH BECAUSE HUH?!?
}
