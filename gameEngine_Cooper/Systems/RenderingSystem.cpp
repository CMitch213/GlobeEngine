#include "RenderingSystem.h"
#include "../Utils/States.h"

void RenderingSystem::tick(ECS::World* world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		//Clear before drawing all textures
		Engine::GetInstance().window->clear();

		world->each<Transform, Sprite2D>(
			[&](ECS::Entity*,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite
				) -> void
			{
				//Check if an entity has their texture loaded.
				if (textureMap.count(sprite->texturePath) < 1) {
					textureMap[sprite->texturePath] = LoadTexture(sprite->texturePath);
				}

				//if no texture is found, then add a texture to the map.
				if (sprite->picture.getTexture() == nullptr) {
					sprite->picture.setTexture(*textureMap[sprite->texturePath]);
					sprite->width = sprite->picture.getGlobalBounds().width;
					sprite->height = sprite->picture.getGlobalBounds().height;
				}

				//Update and draw to the screen
				sprite->picture.setPosition(transform->xPos, transform->yPos);
				Engine::GetInstance().window->draw(sprite->picture);
			}
		);

		//Display updates.
		Engine::GetInstance().window->display();
	}
}

sf::Texture* RenderingSystem::LoadTexture(std::string texturePath)
{
	auto texture = new sf::Texture();
	//auto just means what you are in

	//if texture is not found
	if (texture->loadFromFile(texturePath) == false) {
		std::cerr << "Unable to load image, " << texturePath << "./nIs this image in the correct directory?" << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}

	return texture;
}
