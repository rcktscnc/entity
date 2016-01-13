#ifndef _WORLD_H
#define _WORLD_H

#include "Entity.h"
#include <vector>

namespace ett {
	class World {
	private:
		std::vector<Entity*> players;
	public:
		void add_entity(Entity* _player);
		void collision();
		void process();
		void process_debug(sf::RenderWindow& window);
		void tick();
	};

	void World::add_entity(Entity* _player) {
		players.push_back(_player);
	}

	void World::collision() {

		for (unsigned int i = 0; i < players.size(); i++) {
			players[i]->set_grounded(false);
			for (unsigned int j = i + 1; j < players.size(); j++) {
				
				bool collided = players[i]->test_collision(*players[j]);
				if (collided == true) {
					
					float pixels_up = 0.0f;
					float pixels_left = 0.0f;
					float pixels_down = 0.0f;
					float pixels_right = 0.0f;
					
					sf::Vector2f old_position = players[i]->get_position();

					while (players[i]->test_collision(*players[j]) && pixels_up < 10) {
						players[i]->move(0, -1);
						++pixels_up;
					}

					players[i]->set_position(old_position.x, old_position.y);
					while (players[i]->test_collision(*players[j]) && pixels_left < 10) {
						players[i]->move(-1.0f, 0.0f);
						++pixels_left;
					}

					players[i]->set_position(old_position.x, old_position.y);
					while (players[i]->test_collision(*players[j]) && pixels_down < 10) {
						players[i]->move(0.0f, 1.0f);
						++pixels_down;
					}

					players[i]->set_position(old_position.x, old_position.y);
					while (players[i]->test_collision(*players[j]) && pixels_right < 10) {
						players[i]->move(1.0f, 0.0f);
						++pixels_right;
					}

					players[i]->set_position(old_position.x, old_position.y);

					if (pixels_up < pixels_left && pixels_up < pixels_down &&
							pixels_up < pixels_right) {
						players[i]->set_position(old_position.x, old_position.y - pixels_up);
						players[i]->set_grounded(true);
					} 
					else if (pixels_left < pixels_up && pixels_left < pixels_down &&
							pixels_left < pixels_right) {
						players[i]->set_position(old_position.x - pixels_left, old_position.y);
					}
					else if (pixels_down < pixels_up && pixels_down < pixels_left &&
							pixels_down < pixels_right) {
						players[i]->set_position(old_position.x, old_position.y + pixels_down);
					}
					else if (pixels_right < pixels_up && pixels_right < pixels_down &&
							pixels_right < pixels_up) {
						players[i]->set_position(old_position.x + pixels_right, old_position.y);
					}
				}
			}
		}
	}

	void World::process() {
		for (auto& e : players) e->process();
		collision();
	}

	void World::process_debug(sf::RenderWindow& window) {
		for (auto& e : players) {
			e->process();
			e->draw_shape(window);
		}
		collision();
	}

	void World::tick() {
		for (auto& e : players) e->tick();
	}
}
#endif