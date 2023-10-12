#define _USE_MATH_DEFINES
#include <cmath>
#include "MovementSystem.h"

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<InputController, Transform, Sprite2D>(
		[&](ECS::Entity* entity, 
			ECS::ComponentHandle<InputController> input,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Sprite2D> sprite
			) -> void {
				//Centre anchorpoint to sprite
				// Uncomment if not using spritesheet to set anchor point to centre
				//sprite->picture.setOrigin(sf::Vector2f(sprite->width / 2, sprite->height / 2));
				// 
				//ECS::ComponentHandle<InputController> input = entity->get<InputController>();
				input= entity->get<InputController>();
				if (input->bInputActive==true) {
					if (input->wKey) {
						transform->xSpeed = static_cast<float>(sin(static_cast<double>(sprite->picture.getRotation()) + 90.0 / 180.0 * M_PI) * static_cast<double>(transform->xSpeedMod));
						transform->ySpeed = static_cast<float>(-cos(static_cast<double>(sprite->picture.getRotation()) + 90.0 / 180.0 * M_PI) * static_cast<double>(transform->ySpeedMod));
						transform->Move();
					}
					else if (input->sKey) {
						transform->xSpeed = static_cast<float>(-sin(static_cast<double>(sprite->picture.getRotation()) + 90.0 / 180.0 * M_PI) * static_cast<double>(transform->xSpeedMod));
						transform->ySpeed = static_cast<float>(cos(static_cast<double>(sprite->picture.getRotation()) + 90.0 / 180.0 * M_PI) * static_cast<double>(transform->ySpeedMod));
						transform->Move();
					}
					else {
						transform->xSpeed = 0.0f;
						transform->ySpeed = 0.0f;
					}

					if (input->aKey) {
						sprite->picture.rotate(-transform->rotationSpeed);
					}
					else if (input->dKey) {
						sprite->picture.rotate(transform->rotationSpeed);
					}
				}
		});
}
