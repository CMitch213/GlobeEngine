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
				// comment if using spritesheet to set anchor point to centre
				sprite->picture.setOrigin(sf::Vector2f(sprite->width / 2, sprite->height / 2));
				// 
				//ECS::ComponentHandle<InputController> input = entity->get<InputController>();
				input= entity->get<InputController>();
				if (input->bInputActive==true) {
					if (input->wKey == true)
					{
						transform->xSpeed = sin((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * transform->xSpeedMod;
						transform->ySpeed = -cos((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * transform->ySpeedMod;

						transform->Move();
					}
					else if (input->sKey == true)
					{
						transform->xSpeed = -sin((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * transform->xSpeedMod;
						transform->ySpeed = cos((sprite->picture.getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI)) * transform->ySpeedMod;

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
