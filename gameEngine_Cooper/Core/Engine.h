#pragma once
#include <iostream>
#include "sfml/graphics.hpp"

class Engine
{
public: 
	sf::RenderWindow* window;

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

private:
	void Update();

};

