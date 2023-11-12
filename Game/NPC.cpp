#include "NPC.h"

NPC::NPC(uint16_t id, std::string path, float x, float y, float height, float width, float speed, float MAX_HP, float hp, HPBar_Display display, sf::Color HPColor) :
	Entity(id, path, x, y, height, width, speed, MAX_HP, hp)
{
	this->HPBar = new HealthBar(800.0f, 5.0f, 48.0f, 8.0f, display, HPColor, MAX_HP, hp);
}

Entity_State NPC::ai(const Map& map)
{
	if (map.intersects_with_type(this->get_position().x + this->get_size().x + 2.0f, this->get_position().y + this->get_size().y / 2.0f, Texture_Type::COLLIDABLE_TILE))
	{
		return Entity_State::MOVING_LEFT;
	}
	if (map.intersects_with_type(this->get_position().x - 2.0f, this->get_position().y + this->get_size().y / 2.0f, Texture_Type::COLLIDABLE_TILE))
	{
		return Entity_State::MOVING_RIGHT;
	}
	return facing_right ? Entity_State::MOVING_RIGHT : Entity_State::MOVING_LEFT;
}

void NPC::control(const Map& map, float& time)
{
	if (!is_alive()) { return; }
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

	Entity_State state = ai(map);

	if (state == Entity_State::MOVING_RIGHT) {
		this->dx = this->get_speed_value();
		this->state = Entity_State::MOVING_RIGHT;
		this->frame_move(time);
		this->facing_right = true;
		if (this->get_current_frame() > 6) { this->frame_clear(); }
		this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 35, this->get_size().x, this->get_size().y));
	}
	if (state == Entity_State::MOVING_LEFT)
	{
		this->dx = -this->get_speed_value();
		this->state = Entity_State::MOVING_LEFT;
		this->frame_move(time);
		this->facing_right = false;
		if (this->get_current_frame() > 6) { this->frame_clear(); }
		this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 35, this->get_size().x, this->get_size().y));
	}
}

void NPC::take_damage(float amount, float& time)
{
	if (!is_alive()) { return; }
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

void NPC::heal(float amount)
{
	if (!is_alive()) { return; }
	if (!is_alive()) { return; }
	this->HPBar->heal(amount);
}

void NPC::draw_hearing_circle(sf::RenderWindow& window)
{
	sf::CircleShape circle;
	circle.setPosition(this->get_position().x - hearing_radius + this->get_size().x / 2.0f, this->get_position().y - hearing_radius + this->get_size().y / 2.0f);
	circle.setRadius(this->hearing_radius);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Yellow);
	circle.setOutlineThickness(1.0f);
	window.draw(circle);
}

void NPC::draw_seeing_lines(sf::RenderWindow& window)
{
	sf::Vertex line[2];
	line[0].position = sf::Vector2f(this->get_position().x + this->get_size().x / 2.0f, this->get_position().y + 7.0f);
	line[0].color = sf::Color::Green;
	if (this->facing_right) 
	{
		
		line[1].position = sf::Vector2f(line[0].position.x + 500.0f, line[0].position.y);
		line[1].color = sf::Color::Green;
	}
	else 
	{
		line[1].position = sf::Vector2f(line[0].position.x - 500.0f, line[0].position.y);
		line[1].color = sf::Color::Green;
	}
	window.draw(line, 2, sf::Lines);
}

void NPC::hearing()
{

}

void NPC::seeing()
{

}

void NPC::increase_panic(float amount)
{
	if (!is_alive()) { return; }
	panic = std::min(100.0f, panic + amount);
}

void NPC::decrease_panic(float amount)
{
	if (!is_alive()) { return; }
	panic = std::max(0.0f, panic - amount);
}
