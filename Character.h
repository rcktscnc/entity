#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"
#include "Behavior.h"
#include <memory>
#include <typeinfo>


namespace ett {
	class Character : public Entity {
	private:
		static int id_count;
		int id;
		bool is_on_ground;
		sf::RectangleShape shape;
		sf::Vector2f pos;
		std::vector<std::unique_ptr<Behavior>> bhvrs;
		std::vector<unsigned int> collision_ignored;
		unsigned int derived_hash;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;

	public:
		Character(sf::Vector2f _shape, const sf::Vector2f& _pos);
		int get_id() override;
		void show() override;
		void hide() override;
		void spawn() override;
		void destroy() override;
		void process() override;
		void tick() override;
		void move(float x, float y) override;
		sf::RectangleShape& get_shape() override;
		sf::Vector2f& get_position() override;
		void set_position(float x, float y) override;
		bool test_collision(Entity& _entity) override;
		void draw_shape(sf::RenderWindow& window) override;
		void set_grounded(bool ground) override;
		void set_velocity(float x, float y) override;
		sf::Vector2f get_velocity() override;
		unsigned int get_derived_hash() override;
		std::vector<unsigned int> get_collision_ignored() override;

		void set_shape_color(int r, int g, int b);
		void add_behavior(Behavior* bhvr);
		bool is_grounded();
		void process_force();
		void rotate_shape(float angle);
		template<typename Ignore>
		void ignore_collision();
		template<typename This>
		void init_self();
		
	};

	int Character::id_count = 0;

	Character::Character(sf::Vector2f _shape, const sf::Vector2f& _pos)
			: pos(_pos), shape(_shape), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f) {
		id = id_count++;
		is_on_ground = false;
		shape.setPosition(pos);
		shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(1.0f);
		shape.setOutlineColor(sf::Color(255, 0, 0));
		derived_hash = 0;
	}

	int Character::get_id() { return id; }

	void Character::show() { }

	void Character::hide() { }

	void Character::spawn() { }

	void Character::destroy() { }

	void Character::tick() { }

	void Character::move(float x, float y) { 
		pos.x += x;
		pos.y += y;
		shape.setPosition(pos);
	}

	void Character::set_position(float x, float y) {
		pos.x = x;
		pos.y = y;
		shape.setPosition(pos);
	}

	void Character::draw_shape(sf::RenderWindow& window) { window.draw(shape); }

	sf::RectangleShape& Character::get_shape() { return shape; }

	sf::Vector2f& Character::get_position()  { return pos; }

	void Character::set_shape_color(int r, int g, int b) { shape.setFillColor(sf::Color(r, g, b)); }

	void Character::add_behavior(Behavior* bhvr) { bhvrs.push_back(std::unique_ptr<Behavior>(bhvr)); }

	void Character::process() {
		for (auto& e : bhvrs) {
			e->process();
		}
	}
	
	bool Character::test_collision(Entity& _entity) {
		unsigned int _derived_hash = _entity.get_derived_hash();
		std::vector<unsigned int> ignored_list = _entity.get_collision_ignored();
		for (auto e : collision_ignored) {
			if (e == _derived_hash) return false;
		}
		for (auto e : ignored_list) {
			if (e == derived_hash) return false;
		}
		
		if (shape.getGlobalBounds().intersects(_entity.get_shape().getGlobalBounds()))
			return true;
		else 
			return false;
	}

	void Character::set_grounded(bool ground) { is_on_ground = ground; }

	bool Character::is_grounded() { return is_on_ground; }

	void Character::set_velocity(float x, float y) {
		velocity.x = x;
		velocity.y = y;
	}

	sf::Vector2f Character::get_velocity() {
		return velocity;
	}

	void Character::process_force() {
		move(velocity.x, velocity.y);
	}

	void Character::rotate_shape(float angle) { shape.rotate(angle); }

	template<typename Ignore>
	void Character::ignore_collision() {
		collision_ignored.push_back(typeid(Ignore).hash_code());
	}

	std::vector<unsigned int> Character::get_collision_ignored() {
		return collision_ignored;
	}

	template<typename This>
	void Character::init_self() {
		derived_hash = typeid(This).hash_code();
	}

	unsigned int Character::get_derived_hash() { return derived_hash; }
}
#endif // _CHARACTER_H