#include "Hero.h"

Hero::Hero(uint16_t id, std::string path, float x, float y, float height, float width, float speed, float MAX_HP, float hp) :
	Entity(id, path, x, y, height, width, speed, MAX_HP, hp)
{
	this->HPBar = new HealthBar(5.0f, 5.0f, 96.0f, 16.0f, HPBar_Display::FIXED, sf::Color::Green);
	this->movement = Settings();
}

sf::FloatRect Hero::control(const Map& map, float& time, Entity* entity)
{
	if (!is_alive()) { return sf::FloatRect(0, 0, 0, 0); }
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
		key_pressed = true;
	}

	if (isAttacking) {
		key_pressed = true;
		play_attacking_animation(time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) and !isAttacking) {
		if (attackTimer.getElapsedTime() - lastAttack >= sf::seconds(attackCooldown)) {
			isAttacking = true;
			this->state = Entity_State::ATTACK;
			this->sprite.setTextureRect(sf::IntRect(48 * 4, 140, this->get_size().x, this->get_size().y));
			key_pressed = true;

			lastAttack = attackTimer.getElapsedTime();

			return facing_right ?
				sf::FloatRect(get_position().x + get_size().x + 12.0f, get_position().y, 10.0f, get_size().y) :
				sf::FloatRect(get_position().x - 12.0f, get_position().y, 10.0f, get_size().y);
		}
	}

	if (this->isJumping)
	{
		float temp = 0.5 * time;
		this->frame_move(temp);
		if (this->get_current_frame() >= 4) { this->set_frame(3); }
		this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 68, this->get_size().x, this->get_size().y));
	}

	if (!key_pressed)
	{
		this->frame_move(time);
		if (this->get_current_frame() > 4) { this->frame_clear(); }
		this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 0, this->get_size().x, this->get_size().y));
		this->dx = 0;
	}
	return sf::FloatRect(0, 0, 0, 0);
}

void Hero::take_damage(float amount, float& time)
{
	if (is_dying())
	{
		play_dying_animation(time);
	}
	if (!is_alive()) { return; }
	this->HPBar->take_damage(amount);
	if (HPBar->get_hp() == 0.0f)
	{
		die(time);
	}
}



void Hero::heal(float amount)
{
	if (!is_alive()) { return; }
	this->HPBar->heal(amount);
}


