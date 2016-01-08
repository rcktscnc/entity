#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"
#include "Behavior.h"
#include <vector>

namespace ett {

	const int BODY_SCALE = 10;
	const int WORLD_WIDTH = BODY_SCALE * 80;
	const int WORLD_HEIGHT = BODY_SCALE * 60;

	class Character : public Entity {
	private:
		static int id_count;
		int id;
		sf::RectangleShape shape;
		sf::Texture texture;
		sf::Vector2f pos;
		std::vector<Behavior> bhvrs;
	public:
		Character(const char* file_name, sf::Vector2f _shape, const sf::Vector2f& _pos);
		int get_id() override;
		void show() override;
		void hide() override;
		void spawn() override;
		void destroy() override;
		void move(float x, float y) override;
		void draw_shape(sf::RenderWindow& window);
		sf::RectangleShape& get_shape() override;
		sf::Vector2f& get_position() override;
		void Character::set_position(int x, int y) override;
		void set_color(int r, int g, int b);
		sf::Texture& get_texture();
	};

	int Character::id_count = 0;

	Character::Character(const char* file_name,
		sf::Vector2f _shape, const sf::Vector2f& _pos)
		: pos(_pos), shape(_shape) {
		id = id_count++;
		texture.loadFromFile(file_name);
		shape.setTexture(&texture);
		shape.setPosition(pos);
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

	void Character::set_color(int r, int g, int b) { shape.setFillColor(sf::Color(r, g, b)); }

	sf::Texture& Character::get_texture() { return texture; }
}
#endif // _CHARACTER_H