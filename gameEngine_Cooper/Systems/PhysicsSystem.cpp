#include "PhysicsSystem.h"
#include "../Utils/States.h"


bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity,
	ECS::ComponentHandle<BoxCollider> touchedEntity, float x, float y)
{
	return touchingEntity->rightEdge + x > touchedEntity->leftEdge &&
		touchedEntity->rightEdge > touchingEntity->leftEdge + x &&
		touchingEntity->bottomEdge + y > touchedEntity->topEdge &&
		touchedEntity->bottomEdge > touchingEntity->topEdge + y;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, sf::RectangleShape touchedRectangle,
	float x, float y)
{
	const float touchedRectLeft = touchedRectangle.getPosition().x;
	const float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	const float touchedRectTop = touchedRectangle.getPosition().y;
	const float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

	return touchingEntity->rightEdge + x > touchedRectLeft &&
		touchedRectRight > touchingEntity->leftEdge + x &&
		touchingEntity->bottomEdge + y > touchedRectTop &&
		touchedRectBottom > touchingEntity->topEdge + y;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity,
	ECS::ComponentHandle<RectangleCollider> touchedRectangle, float x, float y)
{
	return touchingEntity->rightEdge + x > touchedRectangle->left &&
		touchedRectangle->right > touchingEntity->leftEdge + x &&
		touchingEntity->bottomEdge + y > touchedRectangle->top &&
		touchedRectangle->bottom > touchingEntity->topEdge + y;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity,
	ECS::ComponentHandle<BoxCollider> touchedEntity)
{
	return touchingEntity->rightEdge > touchedEntity->leftEdge &&
		touchedEntity->rightEdge > touchingEntity->leftEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge &&
		touchedEntity->bottomEdge > touchingEntity->topEdge;
}

void PhysicsSystem::CheckCollisionSides(ECS::ComponentHandle<Transform> transform,
	ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity)
{
	// Scenario dealing with collision from the RIGHT side by accelerating RIGHTWARD
	if (transform->speed.x > 0 &&
		touchedEntity->rightEdge + transform->speed.x > touchedEntity->leftEdge &&
		touchingEntity->topEdge < touchedEntity->bottomEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge)
	{
		transform->speed.x = 0;
	}

	// Scenario dealing with collision from the BOTTOM side by accelerating DOWNWARD
	if (transform->speed.y > 0 &&
		touchedEntity->bottomEdge + transform->speed.y > touchedEntity->topEdge &&
		touchingEntity->leftEdge < touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge)
	{
		transform->speed.y = 0;
	}

	// Scenario dealing with collision from the LEFT side by accelerating LEFTWARD
	if (transform->speed.x < 0 &&
		touchedEntity->leftEdge + transform->speed.x > touchedEntity->rightEdge &&
		touchingEntity->topEdge < touchedEntity->bottomEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge)
	{
		transform->speed.x = 0;
	}

	// Scenario dealing with collision from the TOP side by accelerating UPWARD
	if (transform->speed.x < 0 &&
		touchedEntity->topEdge + transform->speed.y > touchedEntity->bottomEdge &&
		touchingEntity->leftEdge < touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge)
	{
		transform->speed.x = 0;
	}
}

void PhysicsSystem::CheckCollisionSides(ECS::ComponentHandle<Transform> transform,
	ECS::ComponentHandle<BoxCollider> touchingEntity, sf::RectangleShape touchedRectangle)
{
	const float touchedRectLeft = touchedRectangle.getPosition().x;
	const float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	const float touchedRectTop = touchedRectangle.getPosition().y;
	const float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

	// Scenario dealing with collision from the RIGHT side by accelerating RIGHTWARD
	if (transform->speed.x > 0 &&
		touchedRectRight + transform->speed.x > touchedRectLeft &&
		touchingEntity->topEdge < touchedRectBottom &&
		touchingEntity->bottomEdge > touchedRectTop)
	{
		transform->speed.x = 0;
	}

	// Scenario dealing with collision from the BOTTOM side by accelerating DOWNWARD
	if (transform->speed.y > 0 &&
		touchedRectBottom + transform->speed.y > touchedRectTop &&
		touchingEntity->leftEdge < touchedRectRight &&
		touchingEntity->rightEdge > touchedRectLeft)
	{
		transform->speed.y = 0;
	}

	// Scenario dealing with collision from the LEFT side by accelerating LEFTWARD
	if (transform->speed.x < 0 &&
		touchedRectLeft + transform->speed.y > touchedRectRight &&
		touchingEntity->topEdge < touchedRectBottom &&
		touchingEntity->bottomEdge > touchedRectTop)
	{
		transform->speed.x = 0;
	}

	// Scenario dealing with collision from the TOP side by accelerating UPWARD
	if (transform->speed.y < 0 &&
		touchedRectTop + transform->speed.y > touchedRectBottom &&
		touchingEntity->leftEdge < touchedRectRight &&
		touchingEntity->rightEdge > touchedRectLeft)
	{
		transform->speed.y = 0;
	}
}

void PhysicsSystem::CheckCollisionSides(ECS::ComponentHandle<Transform> transform,
	ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<RectangleCollider> touchedRectangle)
{
	// Scenario dealing with collision from the RIGHT side by accelerating RIGHTWARD
	if (transform->speed.x > 0 &&
		touchedRectangle->right + transform->speed.x > touchedRectangle->left &&
		touchingEntity->topEdge < touchedRectangle->bottom &&
		touchingEntity->bottomEdge > touchedRectangle->top)
	{
		transform->speed.x = 0;
	}

	// Scenario dealing with collision from the BOTTOM side by accelerating DOWNWARD
	if (transform->speed.y > 0 &&
		touchedRectangle->bottom + transform->speed.y > touchedRectangle->top &&
		touchingEntity->leftEdge < touchedRectangle->right &&
		touchingEntity->rightEdge > touchedRectangle->left)
	{
		transform->speed.y = 0;
	}

	// Scenario dealing with collision from the LEFT side by accelerating LEFTWARD
	if (transform->speed.x < 0 &&
		touchedRectangle->left + transform->speed.x > touchedRectangle->right &&
		touchingEntity->topEdge < touchedRectangle->bottom &&
		touchingEntity->bottomEdge > touchedRectangle->top)
	{
		transform->speed.x = 0;
	}

	// Scenario dealing with collision from the TOP side by accelerating UPWARD
	if (transform->speed.y < 0 &&
		touchedRectangle->top + transform->speed.y > touchedRectangle->bottom &&
		touchingEntity->leftEdge < touchedRectangle->right &&
		touchingEntity->rightEdge > touchedRectangle->left)
	{
		transform->speed.y = 0;
	}
}

void PhysicsSystem::CheckCollisionSides(ECS::Entity* touchingEntity, ECS::Entity* touchedEntity)
{
	const sf::Vector2f newTouching = touchingEntity->get<Transform>()->position;
	//const float newTouchingY = touchingEntity->get<Transform>()->yPos;
	const sf::Vector2f newTouchingSpeed = touchingEntity->get<Transform>()->speed;
	//const float newTouchingYSpeed = touchingEntity->get<Transform>()->ySpeed;
	const sf::Vector2f newTouched = touchedEntity->get<Transform>()->position;
	//const float newTouchedY = touchedEntity->get<Transform>()->yPos;

	if (newTouching.x > 0 && newTouching.x < newTouched.x)
	{
		touchedEntity->get<Transform>()->position.x++;
	}
	else if (newTouchingSpeed.x < 0 && newTouching.x > newTouched.x)
	{
		touchedEntity->get<Transform>()->position.x--;
	}

	if (newTouchingSpeed.y > 0 && newTouching.y < newTouched.y)
	{
		touchedEntity->get<Transform>()->position.y++;
	}
	else if (newTouchingSpeed.y < 0 && newTouching.y > newTouched.y)
	{
		touchedEntity->get<Transform>()->position.y--;
	}
}

void PhysicsSystem::tick(ECS::World* world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		world->each<BoxCollider, Sprite2D, Transform>(
			[&](ECS::Entity*,
				ECS::ComponentHandle<BoxCollider> collider,
				ECS::ComponentHandle<Sprite2D> sprite,
				ECS::ComponentHandle<Transform> transform
				) -> void
			{
				collider->Update(
					transform->position.x,
					transform->position.y,
					static_cast<float>(sprite->picture.getTextureRect().width),
					static_cast<float> (sprite->picture.getTextureRect().height)
				);
			});

		world->each<BoxCollider>(
			[&](ECS::Entity* touchingEntity,
				ECS::ComponentHandle<BoxCollider> touchingBox
				) -> void
			{
				world->each<BoxCollider>(
					[&](ECS::Entity* touchedEntity,
						ECS::ComponentHandle<BoxCollider> touchedBox
						) -> void
					{
						// Statement to avoid comparing the same entity to itself
						if (touchingEntity->getEntityId() == touchedEntity->getEntityId() || this->IsColliding(touchingBox, touchedBox) == false)
						{
							return;
						}

						// Final collision check
						this->CheckCollisionSides(touchingEntity, touchedEntity);
					});
			});

		world->each<BoxCollider>(
			[&](ECS::Entity* touchingEntity,
				ECS::ComponentHandle<BoxCollider> touchingBox
				) -> void
			{
				world->each<Transform, RectangleCollider>(
					[&](ECS::Entity* touchedEntity,
						ECS::ComponentHandle<Transform> transform,
						ECS::ComponentHandle<RectangleCollider> touchedRectangle
						) -> void
					{
						if (touchingEntity->getEntityId() == touchedEntity->getEntityId() ||
							this->IsColliding(touchingBox, touchedRectangle, transform->position.x, transform->position.y) == false)
						{
							return;
						}

						// Final collision check
						this->CheckCollisionSides(transform, touchingBox, touchedRectangle);
					});
			});

		world->each<Transform>(
			[&](ECS::Entity*,
				ECS::ComponentHandle<Transform> transform
				) -> void
			{
				transform->Move();
			});
	}
}

