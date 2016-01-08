#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "Strip.h"
#include <vector>
namespace ett {
	class Animation {
	private:
		unsigned int i;
		std::vector<Strip*> strips;
	public:
		Animation();
		
		void add_strip(Strip* strip);
		template<typename First, typename... Args>
		void add_strip(First* first, Args*... args);
		void draw();
		void draw(anim_properties ap);
		void set_scale(float x, float y);
	};

	Animation::Animation(): i(0) { }

	void Animation::add_strip(Strip* strip) { strips.push_back(strip); }

	template<typename First, typename... Args>
	void Animation::add_strip(First* first, Args*... args) {
		strips.push_back(first);
		add_strip(args...);
	}

	void Animation::draw(anim_properties ap) {
		if (strips[i]->draw(ap) == false) {
			++i;
			if (i >= strips.size())	i = 0;
			strips[i]->restart_timer();
		}
	}

	void Animation::draw() {
		draw(anim_properties::FORWARD);
	}

	void Animation::set_scale(float x, float y) {
		for (auto& e : strips)
			e->set_scale(x, y);
	}
}
#endif // _ANIMATION_H
