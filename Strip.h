#ifndef _STRIP_H
#define _STRIP_H
#include "Entity.h"

namespace ett {

	enum anim_properties { FORWARD, BACKWARD, 
						   F_UPSIDEDOWN, B_UPSIDEDOWN };

	struct frame_properties {
		int frame_width, frame_height, sheet_offset_x, sheet_offset_y,
			frame_line, max_frames, frame_delay;

		frame_properties() { }
		frame_properties(int _frame_width, int _frame_height, 
						 int _sheet_offset_x, int _sheet_offset_y, 
						 int _frame_line, int _max_frames, 
						 int _frame_delay):
			frame_width(_frame_width),
			frame_height(_frame_height),
			sheet_offset_x(_sheet_offset_x),
			sheet_offset_y(_sheet_offset_y),
			frame_line(_frame_line),
			frame_delay(_frame_delay),
			max_frames(_max_frames)
		{ }
	};
	
	class Strip {
	private:
		int frame_key, current_i;
		frame_properties properties;
		sf::Sprite sprite;
		sf::Clock timer;
		sf::RenderWindow* window;
		Entity* owner;
		sf::Vector2f scale;
	public:
		Strip();
		Strip(sf::Texture& spritesheet, frame_properties& _properties, sf::RenderWindow* window, Entity* _owner);
		void init(sf::Texture& spritesheet, frame_properties& _properties, sf::RenderWindow* _window, Entity* _owner);
		bool draw();
		bool draw(anim_properties ap);
		void set_position(sf::Vector2f _position);
		void set_scale(float x, float y);
		void restart_timer();
	};

	Strip::Strip() { }

	Strip::Strip(sf::Texture& spritesheet, frame_properties& _properties,
				 sf::RenderWindow* _window, Entity* _owner)
		: window(_window), properties(_properties),
		  owner(_owner), frame_key(0), scale(1.0f, 1.0f) 
			{ sprite.setTexture(spritesheet); }

	void Strip::init(sf::Texture& spritesheet, frame_properties& _properties,
		sf::RenderWindow* _window, Entity* _owner) {
			sprite.setTexture(spritesheet);
			properties = _properties;
			window = _window;
			owner = _owner;
			scale.x = 1.0f; scale.y = 1.0f;
	}

	bool Strip::draw(anim_properties ap) {
		sprite.setOrigin(properties.frame_width / 2, properties.frame_height / 2);
		sprite.setPosition(owner->get_position());
		sprite.setTextureRect(
			sf::IntRect(frame_key * properties.frame_width,
			properties.frame_line * properties.frame_height,
			properties.frame_width,
			properties.frame_height));

		if (timer.getElapsedTime().asMilliseconds() >= properties.frame_delay) {
			timer.restart();
			++frame_key;
		}
		
		switch (ap) {
		case anim_properties::BACKWARD:
			sprite.setScale(-scale.x, scale.y); break;
		case anim_properties::FORWARD:
			sprite.setScale(scale.x, scale.y); break;
		case anim_properties::F_UPSIDEDOWN:
			sprite.setScale(scale.x, -scale.y); break;
		case anim_properties::B_UPSIDEDOWN:
			sprite.setScale(-scale.x, -scale.y); break;
		}
		window->draw(sprite);
		if (frame_key == properties.max_frames) {
			frame_key = 0;
			return false;
		}
		else { return true; }
	}

	bool Strip::draw() { return draw(anim_properties::FORWARD); }

	void Strip::set_position(sf::Vector2f _position) {
		sprite.setPosition(_position);
	}

	void Strip::set_scale(float x, float y) {
		scale.x = x;
		scale.y = y;
		sprite.setScale(scale);
	}

	void Strip::restart_timer() { timer.restart(); }
}
#endif // _STRIP_H
