#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"
#include "Behavior.h"
#include <memory>

namespace ett {

	const int BODY_SCALE = 10;
	const int WORLD_WIDTH = BODY_SCALE * 80;
	const int WORLD_HEIGHT = BODY_SCALE * 60;

	class Character : public Entity {
	private:
		static int id_count;
		int id;
		sf::RectangleShape shape;
		sf::Vector2f pos;
		std::vector<std::unique_ptr<Behavior>> bhvrs;
	public:
		Character(sf::Vector2f _shape, const sf::Vector2f& _pos);
		int get_id() override;
		void show() override;
		void hide() override;
		void spawn() override;
		void destroy() override;
		void move(float x, float y) override;
		sf::RectangleShape& get_shape() override;
		sf::Vector2f& get_position() override;
		void set_position(int x, int y) override;
		bool test_collision(Entity& _entity) override;
		void draw_shape(sf::RenderWindow& window);
		void set_shape_color(int r, int g, int b);
		void add_behavior(Behavior* bhvr);
		void process() override;
	};

	int Character::id_count = 0;

	Character::Character(sf::Vector2f _shape, const sf::Vector2f& _pos)
		: pos(_pos), shape(_shape) {
		id = id_count++;
		shape.setPosition(pos);
		shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(1.0f);
		shape.setOutlineColor(sf::Color(255, 0, 0));
	}

	int Character::get_id() { return id; }

	void Character::show() { }

	void Character::hide() { }

	void Character::spawn() { }

	void Character::destroy() { }

	void Character::move(float x, float y) { 
		pos.x += x;
		pos.y += y;
		shape.setPosition(pos);
	}

	void Character::set_position(int x, int y) {
		pos.x = (float)x;
		pos.y = (float)y;
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
		if (shape.getGlobalBounds().intersects(_entity.get_shape().getGlobalBounds()))
			return &_entity;
		else 
			return nullptr;
	}
}
#endif // _CHARACTER_H