#ifndef _CONTROL_H
#define _CONTROL_H

#include "Behavior.h"

namespace ett {
	
	template<typename T>
	class Control : public Behavior {
	private:
		void(T::*func)();
		T* owner;
		sf::Keyboard::Key key;
	public:

		Control(sf::Keyboard::Key _key, void(T::*_func)(), T* _owner);
		void process() override;
	};

	template<typename T>
	Control<T>::Control(sf::Keyboard::Key _key, void(T::*_func)(), T* _owner)
	{
		func = _func;
		key = _key;
		owner = _owner;
	}

	template<typename T>
	void Control<T>::process() { 
		if (sf::Keyboard::isKeyPressed(key)) (owner->*func)();
	}
}

#endif