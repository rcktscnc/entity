#ifndef _DYNAMIC_H
#define _DYNAMIC_H

#include "Behavior.h"

namespace ett {
	template<typename T> 
	class Dynamic : public Behavior {
	private:
		void(T::*func)();
		T* owner;
	public:
		Dynamic(void(T::*_func)(), T* _owner);
		void process() override;
	};

	template<typename T> 
	Dynamic<T>::Dynamic(void(T::*_func)(), T* _owner) {
		owner = _owner;
		func = _func;
	}

	template<typename T>
	void Dynamic<T>::process() {
		(owner->*func)();
	}
}

#endif