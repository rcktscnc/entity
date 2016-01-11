#ifndef _Player_H
#define _Player_H

#include "Character.h"
#include "Animation.h"
#include "Gravity.h"
#include "Control.h"

namespace ett {
	class Player: public Character {
	private:
		Strip anim_running1, anim_running2, 
			  anim_running3, anim_running4, standing;
		Animation running;
		float walk_speed;
		sf::Texture standingTexture;
		sf::Texture runningTexture;
	public:
		Player(sf::RenderWindow& window);
		void move_up();
		void move_left();
		void move_down();
		void move_right();
		void stand(bool face_right);
		void jump();
	};
	Player::Player(sf::RenderWindow& window)
			: Character(sf::Vector2f(40, 70), sf::Vector2f(150, 0)), walk_speed(2.f) {

		Character::add_behavior(new Gravity(0.15f, 0.15f, 0.01f, 7.0f, this));
		Character::add_behavior(new Control<Player>(sf::Keyboard::K, &Player::jump, this));

		standingTexture.loadFromFile("Tim.png");
		standing.init(standingTexture,
			ett::frame_properties(92, 150, 25, 0, 0, 1, 20), &window, this);
		standing.set_scale(0.5, 0.5);

		runningTexture.loadFromFile("dude_animation_sheet.png");
		anim_running1.init(runningTexture,
			ett::frame_properties(130, 145, 0, 0, 0, 7, 20), &window, this);
		anim_running2.init(runningTexture,
			ett::frame_properties(130, 149, 0, 0, 1, 7, 20), &window, this);
		anim_running3.init(runningTexture,
			ett::frame_properties(130, 149, 0, 0, 2, 7, 20), &window, this);
		anim_running4.init(runningTexture,
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
		if (Character::is_grounded())
			Character::set_velocity(-walk_speed, Character::get_velocity().y);
		running.draw(anim_properties::BACKWARD);
	}
	void Player::move_down() {
		Character::move(0, walk_speed);
		//anim_down.draw();
	}
	void Player::move_right() {
		if (Character::is_grounded())
			Character::set_velocity(walk_speed, Character::get_velocity().y);
		running.draw();
	}
	void Player::stand(bool face_right) {
		if(face_right == true)
			standing.draw();
		else standing.draw(anim_properties::BACKWARD);
	}

	void Player::jump() {
		if (Character::is_grounded()) {
			Character::set_velocity(Character::get_velocity().x , -6.0f);
			std::cout << "SPACE!!@\n";
		}
	}
}
#endif // _Player_H