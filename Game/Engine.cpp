	#include "Engine.h"
	#define CURRENT_MAP this->levels[this->current_level]

	Engine::Engine(char** argv, std::string maps_folder_path)
	{
		this->menu = new Menu(WINDOW_LENGTH, WINDOW_HEIGHT, gameState);
		this->texture_manager = new TextureManager(argv);
		this->hero = new Entity(1, "C:/Users/Admin/Desktop/Folders/Astana IT/Courses/Game Development/Development/toxic-wastelands-sfml/Textures/Character_Textures/Biker/biker.png", 34, 325);
		//this->entity_manager = new EntityManager();
		//this->player = new Player("player.png", 32, 100, 32, 32);
		//this->gameover.loadFromFile("gameover.png");
		this->current_level = 0;

		try
		{
			for (const auto& entry : std::filesystem::directory_iterator(maps_folder_path))
			{
				if (std::filesystem::is_regular_file(entry) and entry.path().extension() == ".json")
				{
					this->levels.push_back(this->texture_manager->generate_map(entry.path().string(), BACKGROUND));
				}
				else {
					throw std::exception("Only .json files!\n");
				}
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << "\n";
		}
	}

	void Engine::create_map(std::string path, std::string background_path)
	{
		/* #TODO: TextureManager->generate_map */
	}

	void Engine::create_entity(std::string entity_texture_path, bool is_playable)
	{
		/* #TODO: EntityManager->generate_entity */
	}

	//void Engine::set_view()
	//{
	//	view.setCenter(player->x, player->y);
	//}

	//void Engine::set_focus_on_map(uint16_t id)
	//{
	//	current_level = id;
	//}

	//void Engine::collision()
	//{
	//	/*float tempX = player->x, tempY = player->y;
	//	for (const Layer& layer : levels[current_level].grid)
	//	{
	//		if (layer.is_collidable)
	//		{
	//			for (const Block& block : layer.layer)
	//			{
	//				if (player->hitbox.intersects(block.hitbox))
	//				{
	//					player->x = tempX;
	//					player->y = tempY;
	//					player->sprite.setPosition(tempX, tempY);
	//					player->hitbox.left = tempX;
	//					player->hitbox.top = tempY;
	//				}
	//			}
	//		}
	//	}*/
	//}

	void Engine::check_collisions()
	{
		if (hero->dx > 0 and (CURRENT_MAP.intersects_with_type(hero->x + hero->width, hero->y, Texture_Type::COLLIDABLE_TILE) 
			or CURRENT_MAP.intersects_with_type(hero->x + hero->width, hero->y + hero->height, Texture_Type::COLLIDABLE_TILE)))
		{
			hero->dx = 0;
		}
		if (hero->dx < 0 and (CURRENT_MAP.intersects_with_type(hero->x - TILE_SIZE, hero->y, Texture_Type::COLLIDABLE_TILE)
			or CURRENT_MAP.intersects_with_type(hero->x - TILE_SIZE, hero->y + hero->height, Texture_Type::COLLIDABLE_TILE)))
		{
			hero->dx = 0;
		}
		if (hero->dy > 0 and (CURRENT_MAP.intersects_with_type(hero->x, hero->y + hero->height, Texture_Type::COLLIDABLE_TILE)
			or CURRENT_MAP.intersects_with_type(hero->x + hero->width, hero->y + hero->height, Texture_Type::COLLIDABLE_TILE)))
		{
			hero->dy = 0;
		}
		if (hero->dy < 0 and (CURRENT_MAP.intersects_with_type(hero->x, hero->y, Texture_Type::COLLIDABLE_TILE)
			or CURRENT_MAP.intersects_with_type(hero->x + hero->width, hero->y, Texture_Type::COLLIDABLE_TILE)))
		{
			hero->dy = 0;
		}
	}



	void Engine::menu_loop(sf::RenderWindow& window, float& timer) {
		menu->draw(window);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			menu->MoveUp();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			menu->MoveDown();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if (menu->GetPressedItem() == 0)
			{
				std::cout << "Start button is pressed" << std::endl;
				gameState = "game";
			}
			if (menu->GetPressedItem() == 1)
			{
				std::cout << "Exit button is pressed" << std::endl;
				window.close();
			}
		}
	}

	void Engine::loop(sf::RenderWindow& window, float& timer)
	{
		levels[current_level].draw_map(window);
		hero->draw(window);
			
		hero->control(timer);
		check_collisions();
		hero->move(timer);
		//player->move(timer, levels[current_level]);
		//set_view();
		//player->draw(window);
	}

	Engine::~Engine()
	{
		delete this->texture_manager, this->hero;
	}
