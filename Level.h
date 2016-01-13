#ifndef _LEVEL_H
#define _LEVEL_H

#include "Player.h"
#include "World.h"
#include "Params.h"
#include "Projectile.h"

namespace ett {
	class Level {
	private:
		World world;
		sf::RenderWindow& window;
		sf::Texture background;
		sf::Sprite backgroundSprite;
		sf::View view;
		sf::Vector2f camera_pos;
		////////////////////////////
		ett::Player pl;
		ett::Character floor_0, floor_1, floor_2, floor_3, floor_4, floor_5,
			floor_6, floor_7, floor_8, floor_9, floor_10, floor_11, floor_12;
		int c = 0;
	public:
		Level(sf::RenderWindow& _window);
		void process();
		void tick();
	};

	Level::Level(sf::RenderWindow& _window)
		: window(_window), pl(window),
		floor_0(sf::Vector2f(81, 20), sf::Vector2f(842, 352)),
		floor_1(sf::Vector2f(180, 20), sf::Vector2f(90, 470)),
		floor_2(sf::Vector2f(538, 154), sf::Vector2f(534, 335)),
		floor_3(sf::Vector2f(254, 20), sf::Vector2f(352, 784)),
		floor_4(sf::Vector2f(185, 20), sf::Vector2f(92, 950)),
		floor_5(sf::Vector2f(267, 20), sf::Vector2f(649, 950)),
		floor_6(sf::Vector2f(88, 20), sf::Vector2f(920, 950)),
		floor_7(sf::Vector2f(525, 108), sf::Vector2f(1228, 907)),
		floor_8(sf::Vector2f(427, 20), sf::Vector2f(1705, 950)),
		floor_9(sf::Vector2f(250, 20), sf::Vector2f(1057, 429)),
		floor_10(sf::Vector2f(253, 20), sf::Vector2f(1270, 604)),
		floor_11(sf::Vector2f(340, 20), sf::Vector2f(1752, 428)),
		floor_12(sf::Vector2f(87, 71), sf::Vector2f(1576, 735)) {

		background.loadFromFile("background.png");
		backgroundSprite.setTexture(background);
		view.reset(sf::FloatRect(0.0f, 0.0f, (float)ett::WORLD_WIDTH, (float)ett::WORLD_HEIGHT));
		view.setViewport(sf::FloatRect(0, 0, 1, 1));
		
		world.add_entity(&pl);
		world.add_entity(&floor_0);
		world.add_entity(&floor_1);
		world.add_entity(&floor_2);
		world.add_entity(&floor_3);
		world.add_entity(&floor_4);
		world.add_entity(&floor_5);
		world.add_entity(&floor_6);
		world.add_entity(&floor_7);
		world.add_entity(&floor_8);
		world.add_entity(&floor_9);
		world.add_entity(&floor_10);
		world.add_entity(&floor_11);
		world.add_entity(&floor_12);
		
		camera_pos.x = 0;
		camera_pos.y = 0;
	}

	void Level::process() {
		camera_pos.x = pl.get_position().x - (ett::WORLD_WIDTH / 2);
		camera_pos.y = pl.get_position().y - (ett::WORLD_HEIGHT / 2);
		if (camera_pos.x < 0) camera_pos.x = 0;
		if (camera_pos.x > 1119) camera_pos.x = 1119;
		if (camera_pos.y < 0) camera_pos.y = 0;
		if (camera_pos.y > ett::WORLD_HEIGHT - 170) camera_pos.y = ett::WORLD_HEIGHT - 170;
		view.reset(sf::FloatRect(camera_pos.x, camera_pos.y, (float)ett::WORLD_WIDTH, (float)ett::WORLD_HEIGHT));
		if (pl.get_position().x < 0) pl.set_position(0.0f, pl.get_position().y);
		if (pl.get_position().x > 1919) pl.set_position(1919.0f, pl.get_position().y);


		window.setView(view);
		window.draw(backgroundSprite);
		//world.process_debug(window);
		world.process();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
			world.add_entity(new Projectile(&pl, 500));
			std::cout << ++c << "\n";
		}

	}

	void Level::tick() { world.tick(); }
}
#endif // _LEVEL_H
