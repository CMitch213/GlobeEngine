#include "Engine.h"

void Engine::Update()
{
	sf::Event event;

	while (window->pollEvent(event)) {
		//Close requested event
		if (event.type == sf::Event::Closed) {
			window->close();
		}
	}
}

void Engine::Start(sf::RenderWindow* window)
{
	this->bQuit = false;
	this->window = window;

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
