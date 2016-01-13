#ifndef _Player_H
#define _Player_H

#include "Character.h"
#include "Animation.h"
#include "Gravity.h"
#include "Control.h"
#include "Dynamic.h"

namespace ett {
	class Player: public Character {
	private:
		Strip anim_running1, anim_running2, 
			  anim_running3, anim_running4, standing, jumping;
		Animation running;
		float walk_speed;
		sf::Texture standingTexture;
		sf::Texture runningTexture;
		bool face_right;
	public:
		Player(sf::RenderWindow& window);
		void move_left();
		void move_right();
		void stand_anim();
		void jump();
		void jump_anim();
	};

	Player::Player(sf::RenderWindow& window)
		: Character(sf::Vector2f(35, 70), sf::Vector2f(350, 0)), walk_speed(2.f), face_right(true) {
		Character::init_self<Player>();

		Character::add_behavior(new Gravity(0.15f, 0.15f, 0.01f, 7.0f, this));
		Character::add_behavior(new Control<Player>(sf::Keyboard::Space, &Player::jump, this));
		Character::add_behavior(new Control<Player>(sf::Keyboard::A, &Player::move_left, this));
		Character::add_behavior(new Control<Player>(sf::Keyboard::D, &Player::move_right, this));
		Character::add_behavior(new Dynamic<Player>(&Player::jump_anim, this));
		Character::add_behavior(new Dynamic<Player>(&Player::stand_anim, this));

		standingTexture.loadFromFile("Tim.png");
		standing.init(standingTexture,
			ett::frame_properties(92, 150, 25, 0, 0, 1, 20), &window, this);
		standing.set_scale(0.5, 0.5);

		jumping.init(standingTexture,
			ett::frame_properties(92, 150, 862, 986, 0, 1, 20), &window, this);
		jumping.set_scale(0.5, 0.5);

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

	void Player::move_left() {
		if (Character::is_grounded()) {
			Character::set_velocity(-walk_speed, Character::get_velocity().y);
			running.draw(anim_properties::BACKWARD);
			face_right = false;
		}
	}
	void Player::move_right() {
		if (Character::is_grounded()) {
			Character::set_velocity(walk_speed, Character::get_velocity().y);
			running.draw();
			face_right = true;
		}
	}

	void Player::stand_anim() {
		if (Character::is_grounded()) {
			if (face_right == true) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == false)
					standing.draw();
			} else {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == false)
					standing.draw(anim_properties::BACKWARD);
			}
		}
	}

	void Player::jump() {
		if (Character::is_grounded()) {
			jumping.draw();
			Character::set_velocity(Character::get_velocity().x , -10.0f);
		}
	}
	void Player::jump_anim() {
		if (Character::is_grounded() == false) {
			if (face_right == true) jumping.draw();
			else jumping.draw(anim_properties::BACKWARD);
		}
	}
}
#endif // _Player_H