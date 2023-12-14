#define _USE_MATH_DEFINES
#include <cmath>
#include "GameMovementSystem.h"
#include "Utils/States.h"
#include "Entities/Soldier.h"
#include "Components/GameComponents.h"

void GameMovementSystem::tick(ECS::World* world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		world->each<Transform, Sprite2D, Tag>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite,
				ECS::ComponentHandle<Tag> tag
				) -> void {
					//Centre anchorpoint to sprite
					// comment if using spritesheet to set anchor point to centre
					sprite->picture.setOrigin(sf::Vector2f(sprite->width / 2, sprite->height / 2));

					ECS::ComponentHandle<InputController> input = entity->get<InputController>();
					input = entity->get<InputController>();

					//Set to name of tag of your player character
					if (tag->ContainsTag("Player"))
					{
						if (input->bInputActive == true) {
							//get w key input
							if (input->wKey == true)
							{
								transform->xSpeed = sin((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * transform->xSpeedMod;
								transform->ySpeed = -cos((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * transform->ySpeedMod;

								transform->Move();
							}
							//get s key input
							else if (input->sKey == true)
							{
								transform->xSpeed = -sin((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * transform->xSpeedMod;
								transform->ySpeed = cos((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * transform->ySpeedMod;

								transform->Move();
							}
							//Reset momentum
							else {
								transform->xSpeed = 0.0f;
								transform->ySpeed = 0.0f;
							}

							//get a key input
							if (input->aKey) {
								sprite->picture.rotate(-transform->rotationSpeed);
							}
							//get d key input
							else if (input->dKey) {
								sprite->picture.rotate(transform->rotationSpeed);
							}

							if (input->spaceKey) {
								ECS::ComponentHandle<Shooter> shooter = entity->get<Shooter>();

								if (shooter->timeSinceLastShot >= shooter->fireDelay) {
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
			});
	}
}
