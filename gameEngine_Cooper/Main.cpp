#include "sfml/graphics.hpp"
#include "core/Engine.h"

int main() {

	//Declare & get instance of singleton
	Engine& gameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	//Pass Window Reference to Engine and Start
	gameEngine.Start(&window);
	return 0;

}