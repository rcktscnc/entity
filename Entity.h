#ifndef _ENTITY_H
#define _ENTITY_H
#include <SFML/Graphics.hpp>


namespace ett {
	class Entity {
	public:
		virtual int get_id() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void spawn() = 0;
		virtual void destroy() = 0;
		virtual void move(float x, float y) = 0;
		virtual void set_position(int x, int y) = 0;
		virtual sf::RectangleShape& get_shape() = 0;
		virtual sf::Vector2f& get_position() = 0;
	};
}
#endif // _ENTITY_H