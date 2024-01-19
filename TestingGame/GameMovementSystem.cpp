#define _USE_MATH_DEFINES
#include <cmath>
#include "GameMovementSystem.h"
#include "Utils/States.h"
#include "Entities/Soldier.h"
#include "Components/GameComponents.h"

void GameMovementSystem::tick(ECS::World* world, float deltaTime)
{	
	this->timer += deltaTime;

	if (States::GetPausedState() == false)
	{
		world->each<Transform, Sprite2D, Tag>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite,
				ECS::ComponentHandle<Tag> tag
				) -> void
			{
				// Center anchor point to sprite
				sprite->picture.setOrigin(sf::Vector2f(sprite->width / 2, sprite->height / 2));

				const ECS::ComponentHandle<InputController> input = entity->get<InputController>();

				if (tag->ContainsTag("Player") == true)
				{
					if (input->bInputActive == true)
					{
						if (input->wKey == true)
						{
							transform->speed.x = sin((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * 0.1f;
							transform->speed.y = -cos((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * 0.1f;

							transform->Move();

							std::cout << "X Speed    : " << transform->speed.x << std::endl;
							std::cout << "Y Speed    : " << transform->speed.y << std::endl;
						}
						else if (input->sKey == true)
						{
							transform->speed.x = -sin((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * 0.1f;
							transform->speed.y = cos((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * 0.1f;

							transform->Move();
						}
						else
						{
							transform->speed.x = 0.0f;
							transform->speed.y = 0.0f;
						}

						if (input->aKey == true)
						{
							sprite->picture.rotate(-transform->rotationSpeed * 2);
						}
						else if (input->dKey == true)
						{
							sprite->picture.rotate(transform->rotationSpeed * 2);
						}

						if (input->spaceKey == true)
						{
							const ECS::ComponentHandle<Shooter> shooter = entity->get<Shooter>();

							if (shooter->timeSinceLastShot > shooter->fireDelay)
							{
								entity->get<CallbackEntity>().get()(entity);
								shooter->timeSinceLastShot = 0.0f;
							}
							else
							{
								shooter->timeSinceLastShot += deltaTime;
							}
						}
					}
				}
				else if (tag->ContainsTag("Enemy")) 
				{
					transform->speed.x = sin((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * 0.1f;
					transform->speed.y = -cos((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * 0.1f;

					transform->Move();

					//Random Rotation
					if (this->timer > 10000.0f) {
						int random = std::rand() % 360 + 1;
						sprite->picture.setRotation(random + 90.0f);

						this->timer = 0.0f;
					}

				}
				else if (tag->ContainsTag("Projectile") == true)
				{
					transform->speed.x = sin((transform->rotationAngle + 90.0f) / 180.0f * static_cast<float>(M_PI))/* * transform->xSpeedMod*/;
					transform->speed.y = -cos((transform->rotationAngle + 90.0f) / 180.0f * static_cast<float>(M_PI))/* * transform->ySpeedMod*/;

					transform->Move();
				}
			});
	}
}
