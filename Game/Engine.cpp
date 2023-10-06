#include "Engine.h"

Engine::Engine(char** argv, std::string maps_folder_path)
{
	this->texture_manager = new TextureManager(argv);
	this->entity_manager = new EntityManager();
	this->player = new Player("biker.png", 100, 100, 48, 48);
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
}

void Engine::create_entity(std::string entity_texture_path, bool is_playable)
{
}

void Engine::set_view_on(uint16_t id)
{
}

void Engine::set_focus_on_map(uint16_t id)
{
}

void Engine::collision()
{
	/*float tempX = player->x, tempY = player->y;
	for (const Layer& layer : levels[current_level].grid)
	{
		if (layer.is_collidable)
		{
			for (const Block& block : layer.layer)
			{
				if (player->hitbox.intersects(block.hitbox))
				{
					player->x = tempX;
					player->y = tempY;
					player->sprite.setPosition(tempX, tempY);
					player->hitbox.left = tempX;
					player->hitbox.top = tempY;
				}
			}
		}
	}*/
}

void Engine::loop(sf::RenderWindow& window, float& timer)
{
	levels[current_level].draw_map(window);
	player->move(timer, levels[current_level]);
	player->draw(window);
}

Engine::~Engine()
{
	delete this->texture_manager, this->entity_manager, this->player;
}
