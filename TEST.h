#ifndef _TEST_H
#define _TEST_H

#include "Character.h"
#include "Gravity.h"

namespace ett {
	class TEST : public Character {
	private:
	public:
		TEST() : Character(sf::Vector2f(50, 50), sf::Vector2f(500, 100)) {
			add_behavior(new Gravity(0.15f, 0.15f, 0.01f, 7.0f, this));
		}
	};
}

#endif
