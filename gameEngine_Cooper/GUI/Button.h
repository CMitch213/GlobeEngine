#pragma once
#include "sfml/graphics.hpp"

class Button
{
private:
	sf::Color baseColour, highlightedColour;
	
public:
	//The button
	sf::RectangleShape buttonBG;

	sf::Text buttonText;
	bool bPressed, bClicked, 
		bReleased, bHighlighted;
	
	Button() = default;
	~Button() = default;
	Button(sf::Vector2f size, sf::Color colour, std::string text);
	bool IsHighlighted()const;
	void HighlightButton(sf::RenderWindow* window);
	void Update(sf::Event event, float deltaTime);
	void Render(sf::RenderWindow* window, float deltaTime)const;
	void CheckPressed(sf::Event event);
};

