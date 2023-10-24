#include "Engine.h"
#define CURRENT_MAP this->levels[this->current_level]

Engine::Engine(char** argv, std::string maps_folder_path)
{
	this->texture_manager = new TextureManager(argv);
	this->hero = new Entity(1, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Biker/biker.png", 32, 325, 34, 32);

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
	if (hero->dy > 0 and (CURRENT_MAP.intersects_with_type(hero->x + 2.0f, hero->y + hero->height, Texture_Type::COLLIDABLE_TILE)
		or CURRENT_MAP.intersects_with_type(hero->x + hero->width - 2.0f, hero->y + hero->height, Texture_Type::COLLIDABLE_TILE)))
	{
		hero->dy = 0;
	}
	if ((CURRENT_MAP.intersects_with_type(hero->x + 2.0f, hero->y + hero->height, Texture_Type::COLLIDABLE_TILE)
		or CURRENT_MAP.intersects_with_type(hero->x + hero->width - 2.0f, hero->y + hero->height, Texture_Type::COLLIDABLE_TILE)))
	{
		hero->onGround = true;
		hero->isJumping = false;
	}
	else 
	{
		hero->onGround = false;
		hero->isJumping = true;
	}
	if (hero->dx > 0 and (CURRENT_MAP.intersects_with_type(hero->x + hero->width, hero->y + 2.0f, Texture_Type::COLLIDABLE_TILE)
		or CURRENT_MAP.intersects_with_type(hero->x + hero->width, hero->y + hero->height - 2.0f, Texture_Type::COLLIDABLE_TILE)))
	{
		hero->dx = 0;
	}
	if (hero->dx < 0 and (CURRENT_MAP.intersects_with_type(hero->x, hero->y + 2.0f, Texture_Type::COLLIDABLE_TILE)
		or CURRENT_MAP.intersects_with_type(hero->x, hero->y + hero->height - 2.0f, Texture_Type::COLLIDABLE_TILE)))
	{
		hero->dx = 0;
	}
	
	if (hero->dy < 0 and (CURRENT_MAP.intersects_with_type(hero->x + 2.0f, hero->y, Texture_Type::COLLIDABLE_TILE)
		or CURRENT_MAP.intersects_with_type(hero->x + hero->width - 2.0f, hero->y, Texture_Type::COLLIDABLE_TILE)))
	{
		hero->dy = 0;
	}
}

void Engine::game_loop(sf::RenderWindow& window, float& timer)
{
	hero->draw(window);
	hero->draw_hitbox(window);
	hero->draw_health(window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		hero->take_damage(1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		hero->heal(1.0f);
	}

	hero->control(timer);
	check_collisions();
	hero->apply_gravity(timer);
	hero->move(timer);
}

void Engine::map_loop(sf::RenderWindow& window)
{
	CURRENT_MAP.draw_map(window);
}


Engine::~Engine()
{
	delete this->texture_manager, this->hero;
}
