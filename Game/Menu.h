#pragma once
#include "SFML/Graphics.hpp"

constexpr auto MAX_NUMBER_OF_ITEMS = 2;

class Menu 
{
public: 
	Menu(float width, float height, std::string gameState);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void change_string(std::string gameState);

	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Sprite bg;
};