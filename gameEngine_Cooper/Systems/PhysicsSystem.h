#pragma once
#include "../Core/Engine.h"

class PhysicsSystem : public ECS::EntitySystem
{
public:
	PhysicsSystem() = default;
	~PhysicsSystem() = default;

	bool IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity, float x, float y); //Touching Shape/Entity
	bool IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, sf::RectangleShape touchedRectangle, float x, float y); //Touching A Rectangle
	bool IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<RectangleCollider> touchedRectangle, float x, float y);
	bool IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity);
	void CheckCollisionSides(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity);
	void CheckCollisionSides(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingEntity, sf::RectangleShape touchedRectangle);
	void CheckCollisionSides(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<RectangleCollider> touchedRectangle);
	void CheckCollisionSides(ECS::Entity* touchingEntity, ECS::Entity* touchedEntity);
	void tick(ECS::World* world, float deltaTime) override;
};

