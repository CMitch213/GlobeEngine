#include "MainCamera.h"
#include "../Utils/States.h"

MainCamera::MainCamera(sf::Vector2f pivot)
{
	cameraView.setCenter(pivot);
}

void MainCamera::Update(ECS::World* world, float deltaTime, sf::RenderWindow* window)
{
	float cameraMoveSpeed = 0.1f;

	if (States::GetPausedState() == false) {
		cameraView.setSize(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y));

		//Move Camera
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			cameraView.move(-cameraMoveSpeed * deltaTime, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			cameraView.move(cameraMoveSpeed * deltaTime, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			cameraView.move(0.0f, -cameraMoveSpeed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			cameraView.move(0.0f, cameraMoveSpeed * deltaTime);
		}

		window->setView(cameraView);
	}
}
