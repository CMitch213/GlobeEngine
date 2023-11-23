#include "Engine.h"
#include "../GUI/PauseMenu.h"
#include "../Utils/States.h"
#include "../GUI/MainCamera.h"

void Engine::Update()const
{
	sf::Event event;

	while (window->pollEvent(event)) {
		//Close requested event
		if (event.type == sf::Event::Closed) {
			window->close();
		}

		pauseMenu->Update(event, 10.0f, this->window);
	}

	world->tick(10.0f);
	mainCamera->Update(world, 10.0f, window);
	if (States::GetPausedState()) {
		Pause();
	}
}

void Engine::Start(sf::RenderWindow* window)
{
	this->bQuit = false;
	this->window = window;

	mainCamera = new MainCamera(sf::Vector2f(
		static_cast<uint32_t>(window->getSize().x / 2), 
		static_cast<uint32_t>(window->getSize().y / 2)));
	pauseMenu = new PauseMenu(window);

	//Run the program as long as the window is open
	while (window->isOpen()) {
		Update();
	}
}

Engine& Engine::GetInstance()
{
	static Engine instance;
	return instance;
}

void Engine::AddSystem(ECS::EntitySystem* newSys)
{
	world->registerSystem(newSys);
	world->enableSystem(newSys);
}

void Engine::Pause()const
{
	pauseMenu->Render(window, 10.0f, this->mainCamera->cameraView.getCenter());
}
