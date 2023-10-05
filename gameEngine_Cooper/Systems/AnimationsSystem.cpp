#include "AnimationsSystem.h"

void AnimationsSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<Animator, Sprite2D>(
		[&](ECS::Entity*, ECS::ComponentHandle<Animator> animator, ECS::ComponentHandle<Sprite2D> sprite)->void {

			//By Default, Go to Next Picture.
			animator->currentTime += deltaTime;
			if (animator->currentTime >= animator->nextFrameTime) {
				animator->currentTime = 0;
				animator->currentColumn = (animator->currentColumn + 1) % animator->totalColumns;
			}

			sprite->picture.setTextureRect(sf::IntRect(animator->currentColumn * animator->spriteWidth,		/*For Left/Right Sides*/	
				animator->currentRow * animator->spriteHeight	/*For Top and Bottom Sides*/,
				animator->spriteWidth, animator->spriteHeight	/*For Width and Height*/ ));
		}
		);
}
