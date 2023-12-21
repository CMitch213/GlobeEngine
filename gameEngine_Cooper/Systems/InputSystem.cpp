#include "InputSystem.h"
#include "../Utils/States.h"

InputSystem::InputSystem(sf::RenderWindow* window)
{
	this->window = window;
}

void InputSystem::tick(ECS::World* world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		GetKeyEvents(world);
	}
}

void InputSystem::GetKeyEvents(ECS::World* world)
{
	world->each<InputController>(
		[&](ECS::Entity*, ECS::ComponentHandle<InputController>input)->void {
			input->wKey = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			input->aKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			input->sKey = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			input->dKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			input->spaceKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		}
		);
}
