#include <iostream>
#include "Player.h"
#include "World.h"
#include "Control.h"
#include "TEST.h"

int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(ett::WORLD_WIDTH, ett::WORLD_HEIGHT),
		"MilleniumTEKNoobleSnakeBIT-E", sf::Style::Close);

	int a = 0;
	
	sf::Clock frame_timer;
	int update_delay = 10;

	ett::World world;
	ett::Character floor(sf::Vector2f(700, 50), sf::Vector2f(400, 550));
	ett::Player pl(window), pl2(window);
	ett::TEST test;

	world.add_entity(&pl); world.add_entity(&pl2); world.add_entity(&test);
	world.add_entity(&floor);

	bool face_right = true;

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) { }
			}
		}

		if (frame_timer.getElapsedTime().asMilliseconds() < update_delay)
			continue;
		else
			frame_timer.restart();
		
		world.process();

		floor.draw_shape(window);

		pl2.stand(true);
		pl2.draw_shape(window);
		test.draw_shape(window);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { pl.move_up(); }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { pl.move_left(); face_right = false; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { pl.move_down(); }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { pl.move_right(); face_right = true; }
		else { pl.stand(face_right); }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { pl.jump(); }
		pl.draw_shape(window);

		window.display();
		window.clear();
	}
	return 0;
}