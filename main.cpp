#include <iostream>
#include "Params.h"
#include "Level.h"


int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(ett::WORLD_WIDTH, ett::WORLD_HEIGHT),
		"Entity", sf::Style::Close);

	sf::Clock frame_timer;
	int update_delay = 10;

	ett::Level level(window);

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

		level.process();
		window.display();
		window.clear();
	}
	return 0;
}

/*
int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(ett::WORLD_WIDTH, ett::WORLD_HEIGHT),
		"Entity", sf::Style::Close);

	sf::Texture background;
	background.loadFromFile("background.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(background);

	sf::Clock frame_timer;
	int update_delay = 10;

	ett::World world;
	ett::Player pl(window);
	ett::Character floor(sf::Vector2f(700, 50), sf::Vector2f(400, 550));
	ett::Character floor2(sf::Vector2f(180, 20), sf::Vector2f(90, 470));
	ett::Character floor3(sf::Vector2f(1800, 20), sf::Vector2f(800, 950));
	ett::Character floor4(sf::Vector2f(254, 20), sf::Vector2f(352, 784));

	ett::TEST test;

	world.add_entity(&pl); world.add_entity(&test);	world.add_entity(&floor);
	world.add_entity(&floor2); world.add_entity(&floor3); world.add_entity(&floor4);

	sf::View view;
	view.reset(sf::FloatRect(0, 0, ett::WORLD_WIDTH, ett::WORLD_HEIGHT));
	view.setViewport(sf::FloatRect(0, 0, 1, 1));
	sf::Vector2f camera_pos(0, 0);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {}
			}
		}

		if (frame_timer.getElapsedTime().asMilliseconds() < update_delay)
			continue;
		else
			frame_timer.restart();

		camera_pos.x = pl.get_position().x - (ett::WORLD_WIDTH / 2);
		camera_pos.y = pl.get_position().y - (ett::WORLD_HEIGHT / 2);
		if (camera_pos.x < 0) camera_pos.x = 0;
		if (camera_pos.y < 0) camera_pos.y = 0;
		if (camera_pos.y > ett::WORLD_HEIGHT - 160) camera_pos.y = ett::WORLD_HEIGHT - 160;
		view.reset(sf::FloatRect(camera_pos.x, camera_pos.y, ett::WORLD_WIDTH, ett::WORLD_HEIGHT));

		window.setView(view);
		window.draw(backgroundSprite);
		world.process();
		floor.draw_shape(window);
		floor2.draw_shape(window);
		floor3.draw_shape(window);
		floor4.draw_shape(window);
		test.draw_shape(window);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { pl.move_left(); }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { pl.move_right(); }

		pl.draw_shape(window);

		window.display();
		window.clear();
	}
	return 0;
}
*/