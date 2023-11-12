#pragma once
#include "SFML/Graphics.hpp"
#include "Engine.h"

constexpr auto MAX_NUMBER_OF_ITEMS = 2;

class Menu
{
public:
	Menu(float width, float height, Engine* engine);
	~Menu();

	void draw(sf::RenderWindow& window, Engine* engine);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	Engine* engine;
	int selectedItemIndex;
	int currentFrame = 0;
	int numStartMenu = 100;
	int numDeathMenu = 350;
	int numFinishMenu = 265;
	double frameDuration = 0.05;
	sf::Clock frameClock;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Sprite backgroundSprite;
	std::vector<sf::Texture> frameTextures1, frameTextures2, frameTextures3;
	sf::Texture backgroundTexture;
};