#ifndef _ENTITY_H
#define _ENTITY_H

#include <SFML/Graphics.hpp>
#include <vector>


namespace ett {
	class Entity {
	public:
		virtual int get_id() = 0;
		virtual void show() = 0;
		virtual void hide() = 0;
		virtual void spawn() = 0;
		virtual void destroy() = 0;
		virtual void move(float x, float y) = 0;
		virtual void draw_shape(sf::RenderWindow& window) = 0;
		virtual void set_position(float x, float y) = 0;
		virtual void process() = 0;
		virtual void tick() = 0;
		virtual void set_grounded(bool ground) = 0;
		virtual bool is_grounded() = 0;
		virtual void set_velocity(float x, float y) = 0;
		virtual sf::Vector2f get_velocity() = 0;
		virtual sf::RectangleShape& get_shape() = 0;
		virtual sf::Vector2f& get_position() = 0;
		virtual bool test_collision(Entity& _entity) = 0;
		virtual std::vector<unsigned int> get_collision_ignored() = 0;
		virtual unsigned int get_derived_hash() = 0;
	};
}
#endif // _ENTITY_H