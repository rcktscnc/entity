#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Character.h"
#include "Gravity.h"

namespace ett {
	class Projectile : public Character {
	private:
		Entity* owner;
		unsigned int life_time;
	public:
		Projectile(Entity* _owner, unsigned int _life_time);
	};

	Projectile::Projectile(Entity* _owner, unsigned int _life_time) : Character(sf::Vector2f(10, 10), sf::Vector2f(0, 0)),
		owner(_owner) {
		
		life_time = _life_time;

		sf::Vector2f start_pos = owner->get_position();
		
		add_behavior(new Gravity(0.15f, 0.15f, 0.01f, 7.0f, this));
		
		Character::init_self<Projectile>();

		ignore_collision<Projectile>();

		Character::set_position(start_pos.x + 40, start_pos.y - 40);

		Character::set_velocity(2.f, -4.f);

		
	}
}
#endif