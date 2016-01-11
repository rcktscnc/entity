#ifndef _GRAVITY_H
#define _GRAVITY_H

#include "Behavior.h"
#include "Entity.h"

namespace ett {
	class Gravity : public Behavior {
	private:
		Entity* owner;
		float gforce;
		float friction;
		float air_resistence;
		float terminal_velocity;

	public:
		Gravity(float _gforce, float _friction, float _air_resistance, float _terminal_velocity, Entity* _owner);
		void process() override;
	};

	Gravity::Gravity(float _gforce, float _friction, float _air_resistance, 
		float _terminal_velocity, Entity* _owner)
			: owner(_owner), gforce(_gforce), friction(_friction), 
			air_resistence(_air_resistance), terminal_velocity(_terminal_velocity) { }

	void Gravity::process() {
		sf::Vector2f velocity = owner->get_velocity();
		
		if (owner->is_grounded()) {
			if (velocity.x > 0.0f) {
				if (velocity.x - friction < 0.0f) velocity.x = 0.0f;
				else velocity.x -= friction;
			}
			else if (velocity.x < 0.0f) {
				if (velocity.x + friction > 0.0f) velocity.x = 0.0f;
				else velocity.x += friction;
			}
		}
		else {
			if (velocity.x > 0.0f) {
				if (velocity.x - air_resistence < 0.0f) velocity.x = 0;
				else velocity.x -= air_resistence;
			}
			else if (velocity.x < 0.0f) {
				if (velocity.x + air_resistence > 0.0f) velocity.x = 0;
				else velocity.x += air_resistence;
			}
		}
		
		if (owner->is_grounded() == false || velocity.y < 0.0f) {
			if (velocity.y >= 0) {
				if (velocity.y < terminal_velocity) velocity.y += gforce;
				else velocity.y = terminal_velocity;
			}
			else velocity.y += gforce;
		}
		else 
			velocity.y = 0.0f;

		owner->set_velocity(velocity.x, velocity.y);
		owner->move(velocity.x, velocity.y + 1);
	}
}

#endif
