#include "sfml/graphics.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");

	//Run the program as long as the window is open
	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {
			//Close requested event
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	return 0;

}