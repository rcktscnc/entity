#ifndef _Player_H
#define _Player_H
#include "Character.h"
#include "Animation.h"

namespace ett {
	class Player: public Character {
	private:
		Strip anim_running1, anim_running2, 
			  anim_running3, anim_running4;
		Animation running;
		float walk_speed;
	public:
		Player(sf::RenderWindow& window);
		void move_up();
		void move_left();
		void move_down();
		void move_right();
	};
	Player::Player(sf::RenderWindow& window):
		Character("dude_animation_sheet.png", 
			sf::Vector2f(10, 10), sf::Vector2f(0, 0)),
			walk_speed(0.070f) 
	{
		anim_running1.init(Character::get_texture(), 
			ett::frame_properties(130, 145, 0, 0, 0, 7, 20), 
			&window, this);
		anim_running2.init(Character::get_texture(),
			ett::frame_properties(130, 149, 0, 0, 1, 7, 20), &window, this);
		anim_running3.init(Character::get_texture(),
			ett::frame_properties(130, 149, 0, 0, 2, 7, 20), &window, this);
		anim_running4.init(Character::get_texture(), 
			ett::frame_properties(130, 150, 0, 0, 3, 6, 20), &window, this);
		running.add_strip(&anim_running1, &anim_running2, 
			&anim_running3, &anim_running4);
		running.set_scale(0.5, 0.5);
	}
	void Player::move_up() {
		Character::move(0, -walk_speed);
		//anim_up.draw();
	}
	void Player::move_left() {
		Character::move(-walk_speed, 0);
		running.draw(anim_properties::BACKWARD);
	}
	void Player::move_down() {
		Character::move(0, walk_speed);
		//anim_down.draw();
	}
	void Player::move_right() {
		Character::move(walk_speed, 0);
		running.draw();
		
	}
}
#endif // _Player_H