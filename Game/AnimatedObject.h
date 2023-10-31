#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class AnimatedObject
{
private:
	float x, y, width, height;
	int current_frame;
	int num_of_frames;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	friend class Engine;
	AnimatedObject() = default;
	AnimatedObject(float x, float y, std::string file_path, float width, float height, int num_of_frames);
	AnimatedObject(const AnimatedObject& other);
	AnimatedObject& operator =(const AnimatedObject& other);

	void draw(sf::RenderWindow& window);
	~AnimatedObject() {};
};

