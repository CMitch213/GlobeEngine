#include "PhysicsSystem.h"

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity, float x, float y)
{
    return touchingEntity -> rightEdge + x > touchedEntity -> leftEdge
        && touchedEntity -> rightEdge > touchingEntity -> leftEdge + x 
        && touchingEntity->bottomEdge + y > touchedEntity->topEdge
        && touchedEntity->bottomEdge > touchingEntity->bottomEdge + y;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, sf::RectangleShape touchedRectangle, float x, float y)
{
    const float touchedRectLeft = touchedRectangle.getPosition().x;
    const float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
    const float touchedRectTop = touchedRectangle.getPosition().y;
    const float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

    return touchingEntity->rightEdge + x > touchedRectLeft
        && touchedRectRight > touchingEntity->leftEdge + x
        && touchingEntity->bottomEdge + y > touchedRectTop
        && touchedRectBottom > touchingEntity->topEdge + y;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity)
{
    return touchingEntity->rightEdge > touchedEntity->leftEdge
        && touchedEntity->rightEdge > touchingEntity->leftEdge
        && touchingEntity->bottomEdge > touchedEntity->topEdge
        && touchedEntity->bottomEdge > touchingEntity->topEdge;
}

void PhysicsSystem::CheckCollisionSides(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingEntity, ECS::ComponentHandle<BoxCollider> touchedEntity)
{
    //Scenario dealing with collision from the right side by accelerating right-ward
    if (transform->xSpeed > 0 &&
        touchedEntity->rightEdge + transform->xSpeed > touchedEntity->leftEdge &&
        touchingEntity->topEdge < touchedEntity->bottomEdge &&
        touchingEntity->bottomEdge > touchedEntity->topEdge
        ) {
        transform->xSpeed = 0;
    }

    //Scenario dealing with collision from the bottom side by accelerating down-ward
    if (transform->ySpeed > 0 &&
        touchedEntity->bottomEdge + transform->ySpeed > touchedEntity->topEdge &&
        touchingEntity->leftEdge < touchedEntity->rightEdge &&
        touchingEntity->rightEdge > touchedEntity->leftEdge
        ) {
        transform->ySpeed = 0;
    }

    //Scenario dealing with collision from the left side by accelerating left-ward
    if (transform->xSpeed < 0 &&
        touchedEntity->leftEdge + transform->xSpeed > touchedEntity->rightEdge &&
        touchingEntity->topEdge < touchedEntity->bottomEdge &&
        touchingEntity->bottomEdge > touchedEntity->topEdge
        ) {
        transform->xSpeed = 0;
    }

    //Scenario dealing with collision from the top side by accelerating up-ward
    if (transform->ySpeed < 0 &&
        touchedEntity->topEdge + transform->ySpeed > touchedEntity->bottomEdge &&
        touchingEntity->leftEdge < touchedEntity->rightEdge &&
        touchingEntity->rightEdge > touchedEntity->leftEdge
        ) {
        transform->ySpeed = 0;
    }
}

void PhysicsSystem::CheckCollisionSides(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingEntity, sf::RectangleShape touchedRectangle)
{
    const float touchedRectLeft = touchedRectangle.getPosition().x;
    const float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
    const float touchedRectTop = touchedRectangle.getPosition().y;
    const float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

    //Scenario dealing with collision from the right side by accelerating right-ward
    if (transform->xSpeed > 0 &&
        touchedRectRight + transform-> xSpeed > touchedRectLeft &&
        touchingEntity->topEdge < touchedRectBottom &&
        touchingEntity->bottomEdge > touchedRectTop
        ) {
        transform->xSpeed = 0;
    }

    //Scenario dealing with collision from the bottom side by accelerating down-ward
    if (transform->ySpeed > 0 &&
        touchedRectBottom + transform->ySpeed > touchedRectTop &&
        touchingEntity->leftEdge < touchedRectRight &&
        touchingEntity->rightEdge > touchedRectLeft
        ) {
        transform->ySpeed = 0;
    }

    //Scenario dealing with collision from the left side by accelerating left-ward
    if (transform->xSpeed < 0 &&
        touchedRectLeft + transform->xSpeed > touchedRectRight &&
        touchingEntity->topEdge < touchedRectBottom &&
        touchingEntity->bottomEdge > touchedRectTop
        ) {
        transform->xSpeed = 0;
    }

    //Scenario dealing with collision from the top side by accelerating up-ward
    if (transform->ySpeed < 0 &&
        touchedRectTop + transform->ySpeed > touchedRectBottom &&
        touchingEntity->leftEdge < touchedRectRight &&
        touchingEntity->rightEdge > touchedRectLeft
        ) {
        transform->ySpeed = 0;
    }
}

void PhysicsSystem::CheckCollisionSides(ECS::Entity* touchingEntity, ECS::Entity* touchedEntity)
{
    const float newTouchingX = touchingEntity->get<Transform>()->xPos;
    const float newTouchingY = touchingEntity->get<Transform>()->yPos;
    const float newTouchingXSpeed = touchingEntity->get<Transform>()->xSpeed;
    const float newTouchingYSpeed = touchingEntity->get<Transform>()->ySpeed;
    const float newTouchedX = touchedEntity->get<Transform>()->xPos;
    const float newTouchedY = touchedEntity->get<Transform>()->yPos;

    if (newTouchingXSpeed > 0 && newTouchingX < newTouchedX) {
        touchedEntity->get<Transform>()->xPos++;
    }
    else if (newTouchingXSpeed < 0 && newTouchingX > newTouchedX) {
        touchedEntity->get<Transform>()->xPos--;
    }

    if (newTouchingYSpeed > 0 && newTouchingY < newTouchedY) {
        touchedEntity->get<Transform>()->yPos++;
    }
    else if (newTouchingYSpeed < 0 && newTouchingY > newTouchedY) {
        touchedEntity->get<Transform>()->yPos--;
    }
}

void PhysicsSystem::tick(ECS::World* world, float deltaTime)
{
    world->each<BoxCollider, Sprite2D, Transform>(
        [&](ECS::Entity*,
            ECS::ComponentHandle<BoxCollider> collider,
            ECS::ComponentHandle<Sprite2D> sprite,
            ECS::ComponentHandle<Transform> transform)->void
        {
            collider->Update(transform->xPos, transform->yPos, 
                static_cast<float>(sprite->picture.getTextureRect().width), 
                static_cast<float>(sprite->picture.getTextureRect().height));
        }
    );

    world->each<BoxCollider>(
        [&](ECS::Entity* touchingEntity,
            ECS::ComponentHandle<BoxCollider> touchingBox)->void
        {
            world->each<BoxCollider>(
                [&](ECS::Entity* touchedEntity,
                    ECS::ComponentHandle<BoxCollider> touchedBox)->void
                {
                    //Statement to avoid comparing the same entity to itself
                    if (touchingEntity->getEntityId() == touchedEntity->getEntityId() || this->IsColliding(touchingBox, touchedBox) == false) {
                        return;
                    }
                    //Final Collision Check
                    this->CheckCollisionSides(touchingEntity, touchedEntity);

                });
        });

    world->each<Transform>(
        [&](ECS::Entity*,
            ECS::ComponentHandle<Transform> transform) -> void
        {
            transform->Move();
        });
}
