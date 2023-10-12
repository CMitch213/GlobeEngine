#include "PhysicsSystem.h"

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity, float x, float y)
{
    return false;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, sf::RectangleShape touchedRectangle, float x, float y)
{
    return false;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity)
{
    return false;
}

void PhysicsSystem::CheckCollisionSides(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity)
{
}

void PhysicsSystem::CheckCollisionSides(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingEntity, sf::RectangleShape touchedRectangle)
{
}

void PhysicsSystem::CheckCollisionSides(ECS::Entity* touchingEntity, ECS::Entity* touchedEntity)
{
}

void PhysicsSystem::tick(ECS::World* world, float deltaTime)
{
}
