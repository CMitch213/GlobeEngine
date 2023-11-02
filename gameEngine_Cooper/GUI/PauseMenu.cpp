#include "PauseMenu.h"
#include "../Utils/States.h"
#include "ButtonMap.h"

PauseMenu::PauseMenu(sf::RenderWindow* window)
{
	States::SetPausedState(false);
	this->InitButtons();
}

void PauseMenu::Update(sf::Event event, float deltaTime, sf::RenderWindow* window)
{
	if (event.type == sf::Event::KeyPressed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			//If Unpaused will Pause, If Paused will Unpause
			States::SetPausedState(States::GetPausedState() == false);
		}
	}

	if (States::GetPausedState() == true) {
		std::printf("Game Paused\n");
		ButtonMap::GetMap()["RESUME"]->Update(event, deltaTime);
		ButtonMap::GetMap()["LOAD"]->Update(event, deltaTime);
		ButtonMap::GetMap()["SAVE"]->Update(event, deltaTime);
		ButtonMap::GetMap()["QUIT"]->Update(event, deltaTime);

		//Make button do thing
		//Resume
		if (ButtonMap::GetMap()["RESUME"]->bClicked) {
			States::SetPausedState(States::GetPausedState() == false);
			ButtonMap::GetMap()["RESUME"]->bClicked = false;
		}
		//Quit
		if (ButtonMap::GetMap()["QUIT"]->bClicked) {
			Quit(window);
			ButtonMap::GetMap()["RESUME"]->bClicked = false;
		}
	}
}

void PauseMenu::Render(sf::RenderWindow* window, float deltaTime, sf::Vector2f resumePos)
{
	sf::Font cambria;
	cambria.loadFromFile("../Debug/Fonts/cambria.TTC");
	sf::Vector2f sizeOffset = sf::Vector2f(
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().x / 2.0f,
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().y/ 2.0f
	);
	//Resume Characteristics
	ButtonMap::GetMap()["RESUME"]->buttonBG.setPosition(resumePos + sf::Vector2f(0, -80) - sizeOffset);
	ButtonMap::GetMap()["RESUME"]->buttonText.setFont(cambria);
	ButtonMap::GetMap()["RESUME"]->buttonText.setPosition(ButtonMap::GetMap()["RESUME"]->buttonBG.getPosition());
	ButtonMap::GetMap()["RESUME"]->HighlightButton(window);
	ButtonMap::GetMap()["RESUME"]->Render(window, deltaTime);

	//Load Characteristics
	ButtonMap::GetMap()["LOAD"]->buttonBG.setPosition(resumePos + sf::Vector2f(0, -40) - sizeOffset);
	ButtonMap::GetMap()["LOAD"]->buttonText.setFont(cambria);
	ButtonMap::GetMap()["LOAD"]->buttonText.setPosition(ButtonMap::GetMap()["LOAD"]->buttonBG.getPosition());
	ButtonMap::GetMap()["LOAD"]->HighlightButton(window);
	ButtonMap::GetMap()["LOAD"]->Render(window, deltaTime);

	//Save Characteristics
	ButtonMap::GetMap()["SAVE"]->buttonBG.setPosition(resumePos + sf::Vector2f(0, 0) - sizeOffset);
	ButtonMap::GetMap()["SAVE"]->buttonText.setFont(cambria);
	ButtonMap::GetMap()["SAVE"]->buttonText.setPosition(ButtonMap::GetMap()["SAVE"]->buttonBG.getPosition());
	ButtonMap::GetMap()["SAVE"]->HighlightButton(window);
	ButtonMap::GetMap()["SAVE"]->Render(window, deltaTime);

	//Quit Characteristics
	ButtonMap::GetMap()["QUIT"]->buttonBG.setPosition(resumePos + sf::Vector2f(0, 40) - sizeOffset);
	ButtonMap::GetMap()["QUIT"]->buttonText.setFont(cambria);
	ButtonMap::GetMap()["QUIT"]->buttonText.setPosition(ButtonMap::GetMap()["QUIT"]->buttonBG.getPosition());
	ButtonMap::GetMap()["QUIT"]->HighlightButton(window);
	ButtonMap::GetMap()["QUIT"]->Render(window, deltaTime);

	window->display();
}

void PauseMenu::InitButtons()
{
	sf::Vector2f size(125, 35);
	//Make Buttons
	ButtonMap::GetMap().insert(
		{
			"RESUME", new Button(size, sf::Color(35, 36, 45, 255), "Resume")
		});
	ButtonMap::GetMap().insert(
		{
			"LOAD", new Button(size, sf::Color(35, 36, 45, 255), "Load")
		});
	ButtonMap::GetMap().insert(
		{
			"SAVE", new Button(size, sf::Color(35, 36, 45, 255), "Save")
		});
	ButtonMap::GetMap().insert(
		{
			"QUIT", new Button(size, sf::Color(35, 36, 45, 255), "Close")
		});
}

void PauseMenu::Quit(sf::RenderWindow* window)
{
	window->close();
}
