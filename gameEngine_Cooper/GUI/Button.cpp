#include "Button.h"

Button::Button(sf::Vector2f size, sf::Color colour, std::string text) :
	bPressed(false), bReleased(false), bClicked(false), bHighlighted(false),
	baseColour(colour), highlightedColour(sf::Color(this->baseColour.r + 50, this->baseColour.g + 50, this->baseColour.b + 50, baseColour.a))
{
	buttonBG.setSize(size);
	buttonBG.setFillColor(baseColour);
	buttonBG.setPosition(sf::Vector2f(0, 0));
	buttonText.setCharacterSize(11);
	buttonText.setFillColor(sf::Color(255, 253, 237, 255));
	buttonText.setPosition(sf::Vector2f(0, 0));
	buttonText.setString(text);
}

bool Button::IsHighlighted()const
{
	return bHighlighted;
}

void Button::HighlightButton(sf::RenderWindow* window)
{
	bHighlighted = buttonBG.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));

	if (bHighlighted) {
		buttonBG.setFillColor(highlightedColour);
	}
	else {
		buttonBG.setFillColor(baseColour);
	}
}

void Button::Update(sf::Event event, float deltaTime)
{
	CheckPressed(event);
}

void Button::Render(sf::RenderWindow* window, float deltaTime)const
{
	window->draw(buttonBG);
	window->draw(buttonText);
	window->display();
}

//TODO
void Button::CheckPressed(sf::Event event)
{
	if (bHighlighted == false) {
		return;
	}

	if (event.type == sf::Event::MouseButtonPressed) {
		bPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		if (!bPressed) {
			bClicked = false;
		}
	}

	if (bPressed) {
		if (event.type == sf::Event::MouseButtonReleased) {
			bReleased = true;
			bClicked = true;
		}
		else {
			bReleased = false;
			bClicked = false;
		}
	}
}
