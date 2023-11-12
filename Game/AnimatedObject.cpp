#include "AnimatedObject.h"

AnimatedObject::AnimatedObject(float x, float y, std::string file_path, float width, float height, int num_of_frames) :
	x(x), y(y), num_of_frames(num_of_frames), width(width), height(height), current_frame(0)
{
	this->image.loadFromFile(file_path);
	//this->image.createMaskFromColor(sf::Color::White);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(static_cast <int>(this->width) * current_frame, 0, this->width, this->height));
	this->sprite.setPosition(this->x, this->y);
}

void AnimatedObject::draw(sf::RenderWindow& window, float& timer)
{
	if (this->current_frame >= this->num_of_frames) { this->current_frame = 0; }
	this->current_frame += 0.005 * timer;

	this->sprite.setTextureRect(sf::IntRect(static_cast <int>(this->width) * static_cast <int>(current_frame), 0, this->width, this->height));
	window.draw(this->sprite);
}

AnimatedObject::AnimatedObject(const AnimatedObject& other)
{
	this->x = other.x; this->y = other.y;
	this->width = other.width; this->height = other.height;
	this->current_frame = 0;
	this->num_of_frames = other.num_of_frames;
	this->image = other.image;
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(static_cast <int>(this->width) * current_frame, 0, this->width, this->height));
	this->sprite.setPosition(this->x, this->y);
}

AnimatedObject& AnimatedObject::operator=(const AnimatedObject& other)
{
	if (this != &other)
	{
		this->x = other.x; this->y = other.y;
		this->width = other.width; this->height = other.height;
		this->current_frame = 0;
		this->num_of_frames = other.num_of_frames;
		this->image = other.image;
		this->texture.loadFromImage(this->image);
		this->sprite.setTexture(this->texture);
		this->sprite.setTextureRect(sf::IntRect(static_cast <int>(this->width) * current_frame, 0, this->width, this->height));
		this->sprite.setPosition(this->x, this->y);
	}
	return *this;
}
