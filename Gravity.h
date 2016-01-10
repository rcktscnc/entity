#ifndef _GRAVITY_H
#define _GRAVITY_H

#include "Behavior.h"
#include "Entity.h"

namespace ett {
	class Gravity : public Behavior {
	private:
		Entity* owner;
		float acceleration;
	public:
		Gravity(float _acceleration, Entity* _owner);
		void process() override;
	};

	Gravity::Gravity(float _acceleration, Entity* _owner)
		: owner(_owner), acceleration(_acceleration) { }

	void Gravity::process() {
		if (true) { // work on this
			owner->set_position(owner->get_position().x,
				owner->get_position().y + acceleration);
		}
	}


}

#endif
