#include "sfml/graphics.hpp"
#include "core/Engine.h"

int main() {

	//Declare & get instance of singleton
	Engine& gameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	
	//Create the world
	gameEngine.world = ECS::World::createWorld();

	//Create entities
	ECS::Entity* stickFigure;

	//Add systems to the engine
	gameEngine.AddSystem(new RenderingSystem());

	//Create and assign 250 enitities to the world
	for (int x = 0; x < 25; x++) {
		for (int y = 0; y < 10; y++)
		{
			stickFigure = gameEngine.world->create();

			//Assign components to entities
			stickFigure->assign<Transform>(x * 25 /*width of img*/, y * 32 /*height of img*/);
			stickFigure->assign<Sprite2D>("../Debug/Pics/hero.png");

			std::cout << "Entity ID: " << stickFigure->getEntityId() << std::endl;
		}
	}

	//Pass Window Reference to Engine and Start
	gameEngine.Start(&window);
	return 0;
}