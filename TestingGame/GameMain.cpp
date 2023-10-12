#include "sfml/graphics.hpp"
#include "../gameEngine_Cooper/Core/Engine.h"
#include "../gameEngine_Cooper/Systems/InputSystem.h"
#include "../gameEngine_Cooper/Systems/MovementSystem.h"

int main() {

	//Declare & get instance of singleton
	Engine& gameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");

	//Create the world
	gameEngine.world = ECS::World::createWorld();

	//Create entities
	ECS::Entity* background;
	ECS::Entity* tux;
	ECS::Entity* stickFigure;

	//Add systems to the engine
	gameEngine.AddSystem(new RenderingSystem());
	gameEngine.AddSystem(new AnimationsSystem());
	gameEngine.AddSystem(new InputSystem(&window));
	gameEngine.AddSystem(new MovementSystem());

	//Create Entities
	background = gameEngine.world->create();
	tux = gameEngine.world->create();
	stickFigure = gameEngine.world->create();

	//Assign Componets to Entities
	background->assign<Transform>(0, 0);
	background->assign<Sprite2D>("../Debug/Pics/bg.jpg");
	tux->assign<Transform>(50, 50, 0.3f, 0.3f, 0.0f, 0.2f);
	tux->assign<Sprite2D>("../Debug/Pics/tux_from_linux.png");
	tux->assign<Animator>(56, 72, 3, 9, 3000.0f);
	tux->get<Animator>()->currentRow = 0;
	tux->assign<InputController>();
	stickFigure->assign<Transform>(100, 100);
	stickFigure->assign<Sprite2D>("../Debug/Pics/herosheet.png");
	stickFigure->assign<Animator>(32, 32, 4, 1, 2000.0f);

	//Check Which Entity They Are
	std::cout << "EntityID: " << background->getEntityId() << std::endl;
	std::cout << "EntityID: " << tux->getEntityId() << std::endl;
	std::cout << "EntityID: " << stickFigure->getEntityId() << std::endl;


	////Create and assign 250 enitities to the world
	//for (int x = 0; x < 25; x++) {
	//	for (int y = 0; y < 10; y++)
	//	{
	//		stickFigure = gameEngine.world->create();

	//		//Assign components to entities
	//		stickFigure->assign<Transform>(x * 25 /*width of img*/, y * 32 /*height of img*/);
	//		stickFigure->assign<Sprite2D>("../Debug/Pics/hero.png");

	//		std::cout << "Entity ID: " << stickFigure->getEntityId() << std::endl;
	//	}
	//}


	//Pass Window Reference to Engine and Start
	gameEngine.Start(&window);
	return 0;
}