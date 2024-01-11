#include "Projectile.h"

Projectile::Projectile(ECS::World* world, const size_t id, /*Soldier& shooter, const std::string picturePath,*/ sf::Vector2f position, float angle, float speed) :
	ECS::Entity(world, id)
{
	Engine& engine = Engine::GetInstance();
	engine.world = world;
	this->id = id;

	this->entity = engine.world->create();
	this->entity->assign<Sprite2D>("../Debug/Pics/Projectile.png");
	this->entity->assign<Tag>();
	this->entity->get<Tag>()->AddTag("Projectile");
	this->entity->assign<Transform>(sf::Vector2f(position.x, position.y), sf::Vector2f(speed, speed), angle, speed);
}

Projectile::~Projectile()
{
	Engine& engine = Engine::GetInstance();
	engine.world->destroy(this->entity);
}
