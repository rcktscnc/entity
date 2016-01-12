#ifndef _LEVEL_H
#define _LEVEL_H

#include "Player.h"
#include "World.h"
#include "Params.h"

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
		ett::Character floor_0, floor_1, floor_2, floor_3;
	public:
		Level(sf::RenderWindow& _window);
		void process();

	};

	Level::Level(sf::RenderWindow& _window)
		: window(_window), pl(window),
		floor_0(sf::Vector2f(700, 50), sf::Vector2f(400, 550)),
		floor_1(sf::Vector2f(180, 20), sf::Vector2f(90, 470)),
		floor_2(sf::Vector2f(1800, 20), sf::Vector2f(800, 950)),
		floor_3(sf::Vector2f(254, 20), sf::Vector2f(352, 784)) {

		background.loadFromFile("background.png");
		backgroundSprite.setTexture(background);
		view.reset(sf::FloatRect(0.0f, 0.0f, (float)ett::WORLD_WIDTH, (float)ett::WORLD_HEIGHT));
		view.setViewport(sf::FloatRect(0, 0, 1, 1));
		world.add_entity(&pl); world.add_entity(&floor_0);
		world.add_entity(&floor_1); world.add_entity(&floor_2); 
		world.add_entity(&floor_3);
		camera_pos.x = 0;
		camera_pos.y = 0;
	}

	void Level::process() {
		camera_pos.x = pl.get_position().x - (ett::WORLD_WIDTH / 2);
		camera_pos.y = pl.get_position().y - (ett::WORLD_HEIGHT / 2);
		if (camera_pos.x < 0) camera_pos.x = 0;
		if (camera_pos.y < 0) camera_pos.y = 0;
		if (camera_pos.y > ett::WORLD_HEIGHT - 160) camera_pos.y = ett::WORLD_HEIGHT - 160;
		view.reset(sf::FloatRect(camera_pos.x, camera_pos.y, (float)ett::WORLD_WIDTH, (float)ett::WORLD_HEIGHT));

		window.setView(view);
		window.draw(backgroundSprite);
		world.process_debug(window);
		//world.process();
	}

}
#endif // _LEVEL_H
