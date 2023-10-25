#include "Menu.h"

Menu::Menu(float width, float height, std::string gameState)
{
	if (!font.loadFromFile("C:/Users/Admin/Desktop/Folders/Astana IT/Courses/Game Development/Development/toxic-wastelands-sfml/Fonts/QuantifierNbp-2d6X.ttf"))
	{
		// handle error
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	change_string(gameState);
	menu[0].setCharacterSize(40);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Exit");
	menu[1].setCharacterSize(40);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.5));

	selectedItemIndex = 0;
}
	
Menu::~Menu() {
}

void Menu::change_string(std::string gameState) 
{
	if (gameState == "menu")
	{
		menu[0].setString("Play");
	}
	if (gameState == "death")
	{
		menu[0].setString("Replay");
	}
}

void Menu::draw(sf::RenderWindow& window)
{

	window.draw(bg);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}