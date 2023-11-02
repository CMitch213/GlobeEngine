#pragma once
#include "../Core/Engine.h"
class PauseMenu
{
public:
	PauseMenu() = default;
	~PauseMenu() = default;
	PauseMenu(sf::RenderWindow* window);
	void Update(sf::Event event, float deltaTime, sf::RenderWindow* window);
	void Render(sf::RenderWindow* window, float deltaTime, sf::Vector2f resumePos);

private:
	void InitButtons();
	void Quit(sf::RenderWindow* window);
};

