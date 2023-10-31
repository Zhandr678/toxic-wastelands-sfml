#include "Hero.h"

Hero::Hero(uint16_t id, std::string path, float x, float y, float height, float width, float speed, float MAX_HP, float hp) :
	Entity(id, path, x, y, height, width, speed, MAX_HP, hp)
{
	this->movement = Settings();
}

void Hero::control(float& time)
{
	if (!this->facing_right) {
		sf::Vector2f currentPosition = this->sprite.getPosition();
		this->sprite.setOrigin(this->sprite.getLocalBounds().width, 0.0f);
		this->sprite.setScale({ -1, 1 });
		this->sprite.setPosition(currentPosition);
	}
	else {
		this->sprite.setOrigin(0, 0);
		this->sprite.setScale({ 1, 1 });
	}

	bool key_pressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->dx = this->get_speed_value();
		this->state = Entity_State::MOVING_RIGHT;
		this->frame_move(time);
		this->facing_right = true;
		if (this->get_current_frame() > 6) { this->frame_clear(); }
		this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 35, this->get_size().x, this->get_size().y));
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->dx = -this->get_speed_value();
		this->state = Entity_State::MOVING_LEFT;
		this->frame_move(time);
		this->facing_right = false;
		if (this->get_current_frame() > 6) { this->frame_clear(); }
		this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 35, this->get_size().x, this->get_size().y));
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and this->is_on_ground() and !this->is_jumping())
	{
		this->dy = -3 * this->get_speed_value();
		this->state = Entity_State::JUMP;
		this->set_off_ground();
		this->set_jumping();
	}
	if (!key_pressed)
	{
		this->frame_move(time);
		if (this->get_current_frame() > 4) { this->frame_clear(); }
		this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 0, this->get_size().x, this->get_size().y));
		this->dx = 0;
	}
}

void Hero::take_damage(float amount)
{
	this->HPBar->take_damage(amount);
}

void Hero::heal(float amount)
{
	this->HPBar->heal(amount);
}


