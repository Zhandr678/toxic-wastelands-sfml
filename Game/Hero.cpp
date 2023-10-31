#include "Hero.h"

Hero::Hero(uint16_t id, std::string path, float x, float y, float height, float width, float speed, float MAX_HP, float hp) :
	Entity(id, path, x, y, height, width, speed, MAX_HP, hp)
{
	this->movement = Settings();
}

void Hero::control(float& time)
{
	sf::Sprite& change = this->this_sprite();
	if (this->is_facing_left()) {
		sf::Vector2f currentPosition = change.getPosition();
		change.setOrigin(change.getLocalBounds().width, 0.0f);
		change.setScale({ -1, 1 });
		change.setPosition(currentPosition);
	}
	else {
		change.setOrigin(0, 0);
		change.setScale({ 1, 1 });
	}

	bool key_pressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->set_dx(this->get_speed_value());
		this->set_state(Entity_State::MOVING_RIGHT);
		this->frame_move_by(0.005 * time);
		this->set_facing_right(true);
		if (this->get_current_frame() > 6) { this->frame_move_by(-this->get_current_frame()); }
		change.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 35, this->get_size().x, this->get_size().y));
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->set_dx(-this->get_speed_value());
		this->set_state(Entity_State::MOVING_LEFT);
		this->frame_move_by(0.005 * time);
		this->set_facing_right(false);
		if (this->get_current_frame() > 6) { this->frame_move_by(-this->get_current_frame()); }
		change.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 35, this->get_size().x, this->get_size().y));
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and this->is_on_ground() and !this->is_jumping())
	{
		this->set_dy(-3 * this->get_speed_value());
		this->set_state(Entity_State::JUMP);
		this->set_on_ground(false);
		this->set_jumping(true);
	}
	if (!key_pressed)
	{
		this->frame_move_by(0.005 * time);
		if (this->get_current_frame() > 4) { this->frame_move_by(-this->get_current_frame()); }
		change.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 0, this->get_size().x, this->get_size().y));
		this->set_dx(0);
	}
}

void Hero::take_damage(float amount)
{
	this->this_HPBar()->take_damage(amount);
}

void Hero::heal(float amount)
{
	this->this_HPBar()->heal(amount);
}


