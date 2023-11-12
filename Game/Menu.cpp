#include "Menu.h"

#include "Engine.h"

Menu::Menu(float width, float height, Engine* engine)
{
	if (!font.loadFromFile("C:/Users/Home/source/repos/Game/Fonts/QuantifierNbp-2d6X.ttf"))
	{
		std::cout << "Error loading font\n" << std::endl;
	}
	for (int i = 0; i <= numStartMenu; i++) {
		std::string frameFileName = "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Menus/start_menu/start_menu_anim-" + std::to_string(i) + ".png";
		if (!backgroundTexture.loadFromFile(frameFileName)) {
			std::cout << "Error loading Menu.gif\n" << std::endl;
		}
		frameTextures1.push_back(backgroundTexture);
	}
	for (int i = 0; i <= numDeathMenu; i++) {
		std::string frameFileName = "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Menus/death_menu/death_menu_anim-" + std::to_string(i) + ".png";
		if (!backgroundTexture.loadFromFile(frameFileName)) {
			std::cout << "Error loading Death_Menu.gif\n" << std::endl;
		}
		frameTextures2.push_back(backgroundTexture);
	}
	for (int i = 0; i <= numFinishMenu; i++) {
		std::string frameFileName = "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Menus/finish_menu/3-" + std::to_string(i) + ".png";
		if (!backgroundTexture.loadFromFile(frameFileName)) {
			std::cout << "Error loading Death_Menu.gif\n" << std::endl;
		}
		frameTextures3.push_back(backgroundTexture);
	}

	if (engine->getGameState() == Game_State::MENU) {
		menu[0].setString("Play");
		menu[0].setPosition(sf::Vector2f(width / 2.13, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.32));
		menu[1].setPosition(sf::Vector2f(width / 2.13, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.71));
	}
	if (engine->getGameState() == Game_State::DEATH) {
		menu[0].setString("Replay");
		menu[0].setPosition(sf::Vector2f(width / 2.2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.32));
		menu[1].setPosition(sf::Vector2f(width / 2.13, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.71));
	}
	if (engine->getGameState() == Game_State::FINISH) {
		menu[0].setString("Play again");
		menu[0].setPosition(sf::Vector2f(width / 2.35, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.15));
		menu[1].setPosition(sf::Vector2f(width / 2.13, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.5));
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setCharacterSize(45);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Exit");
	menu[1].setCharacterSize(45);

	selectedItemIndex = 0;
}

Menu::~Menu() {
}


void Menu::draw(sf::RenderWindow& window, Engine* engine)
{
	if (engine->getGameState() == Game_State::MENU) {
		if (frameClock.getElapsedTime().asSeconds() >= frameDuration) {
			currentFrame = (currentFrame + 1) % numStartMenu;
			backgroundSprite.setTexture(frameTextures1[currentFrame]);
			frameClock.restart();
		}
	}
	if (engine->getGameState() == Game_State::DEATH) {
		if (frameClock.getElapsedTime().asSeconds() >= frameDuration) {
			currentFrame = (currentFrame + 1) % numDeathMenu;
			backgroundSprite.setTexture(frameTextures2[currentFrame]);
			frameClock.restart();
		}
	}
	if (engine->getGameState() == Game_State::FINISH) {
		if (frameClock.getElapsedTime().asSeconds() >= 0.08) {
			currentFrame = (currentFrame + 1) % numFinishMenu;
			backgroundSprite.setTexture(frameTextures3[currentFrame]);
			frameClock.restart();
		}
	}
	window.draw(backgroundSprite);

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
