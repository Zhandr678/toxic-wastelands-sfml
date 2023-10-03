#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Block
{
private:
	uint16_t id;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float height, width;
	float x, y;
public:
	Block() = delete;
	Block(uint16_t id, std::string file, float x, float y);
	Block(const Block& other);
	Block& operator =(const Block& other);

	void create_mask_from_color(sf::Color color);
	void draw(sf::RenderWindow& window) const;
	
	~Block() {};
};

