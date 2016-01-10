#ifndef _COLLISION_H
#define _COLLISION_H

#include "Entity.h"
#include "Behavior.h"

namespace ett {
	class Collision : public Behavior {
	private:
		Entity* owner;
	public:
		Collision(Entity* _owner);
		void process() override;
		bool check_collision();
	};

	Collision::Collision(Entity* _owner) : owner(_owner) {

	}

	void Collision::process() {

	}

	bool Collision::check_collision() {
		
		return true;
	}
}
#endif
