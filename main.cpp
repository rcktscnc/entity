#include <iostream>
#include "Player.h"
#include "Animation.h"

int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(ett::WORLD_WIDTH, ett::WORLD_HEIGHT),
		"MilleniumTEKNoobleSnakeBIT-E", sf::Style::Close);

	sf::Clock frame_timer;
	
	ett::Player pl(window);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) { }
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { pl.move_up(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { pl.move_left(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { pl.move_down(); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { pl.move_right(); }

		window.display();
		window.clear();
	}
	return 0;
}