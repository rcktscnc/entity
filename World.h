#ifndef _WORLD_H
#define _WORLD_H

#include "Entity.h"
#include <vector>
#include <memory>
#include <iostream>

namespace ett {
	class World {
	private:
		std::vector<Entity*> players;
	public:
		void add_entity(Entity* _player);
		void collision();
		void process();
	};

	void World::add_entity(Entity* _player) {
		players.push_back(_player);
	}

	void World::collision() {
		for (int i = 0; i < players.size(); i++) {
			for (int j = i + 1; j < players.size(); j++) {
				bool collided = players[i]->test_collision(*players[j]);
				if (collided == true) {
					std::cout << "SHAPE " << players[i]->get_id() 
						<< " COLLIDES WITH " << players[j]->get_id() << "\n";

					int pixels_up = 0;
					int pixels_left = 0;
					int pixels_down = 0;
					int pixels_right = 0;

					sf::Vector2f old_position = players[i]->get_position();

					while (players[i]->test_collision(*players[j])) {
						++pixels_up;
						players[i]->set_position(players[i]->get_position().x,
							players[i]->get_position().y - 1);
					}

					players[i]->set_position(old_position.x, old_position.y);
					while (players[i]->test_collision(*players[j])) {
						++pixels_left;
						players[i]->set_position(players[i]->get_position().x - 1,
							players[i]->get_position().y);
					}

					players[i]->set_position(old_position.x, old_position.y);
					while (players[i]->test_collision(*players[j])) {
						++pixels_down;
						players[i]->set_position(players[i]->get_position().x,
							players[i]->get_position().y + 1);
					}

					players[i]->set_position(old_position.x, old_position.y);
					while (players[i]->test_collision(*players[j])) {
						++pixels_right;
						players[i]->set_position(players[i]->get_position().x + 1,
							players[i]->get_position().y);
					}

					players[i]->set_position(old_position.x, old_position.y);

					if (pixels_up < pixels_left &&
						pixels_up < pixels_down &&
						pixels_up < pixels_right) {
						players[i]->set_position(old_position.x, old_position.y - pixels_up);
					} 
					else if (pixels_left < pixels_up &&
						pixels_left < pixels_down &&
						pixels_left < pixels_right) {
						players[i]->set_position(old_position.x - pixels_left, old_position.y);
					}
					else if (pixels_down < pixels_up &&
						pixels_down < pixels_left &&
						pixels_down < pixels_right) {
						players[i]->set_position(old_position.x, old_position.y + pixels_down);
					}
					else if (pixels_right < pixels_up &&
						pixels_right < pixels_down &&
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

}
#endif

/*players[i]->set_position(players[i]->get_position().x + 1,
players[i]->get_position().y);*/