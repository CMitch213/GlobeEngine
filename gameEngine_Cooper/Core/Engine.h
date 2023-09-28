#pragma once
#include <iostream>
#include "sfml/graphics.hpp"
#include "ECS.h"
#include "Components.h"
#include "../Systems/RenderingSystem.h"

class Engine
{
public: 
	sf::RenderWindow* window;
	ECS::World* world;

private:
	bool bQuit;
	Engine() = default;
	~Engine() = default;

public:
	//Required to prevent the reference from being copied, moved, or assigned. (MAKE NO OBJECTS OF THIS)
	//= delete mean that if you try to say things before hand throws an error
	Engine(Engine& copy) = delete; //Hide copy constructor
	Engine(Engine&& other) = delete; //Hide moved constructor
	Engine& operator= (Engine& copy) = delete; //Hide assignment operator (Bans = sign)
	void Start(sf::RenderWindow* window);
	static Engine& GetInstance();
	void AddSystem(ECS::EntitySystem* newSys);

private:
	void Update();

};

