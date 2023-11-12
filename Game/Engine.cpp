#include "Engine.h"
#define CURRENT_MAP this->levels[this->current_level]

Engine::Engine(char** argv)
{
	this->menu = new Menu(WINDOW_LENGTH, WINDOW_HEIGHT, this);
	init_view();
	this->file_manager = new FileManager(argv);
	this->texture_manager = new TextureManager(argv);
	this->entity_manager = new EntityManager();

	this->hero = new Hero(1, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Biker/biker.png", 32, 325, 34, 32);
	this->entity_manager->push(EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Cyborg/cyborg.png", 32 * 3, WINDOW_HEIGHT - 32 * 2.5, 32, 34, 0.0, 100, 100, HPBar_Display::BOUND, sf::Color::Red, false);
	this->entity_manager->push(EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Cyborg/cyborg.png", 26 * 32, WINDOW_HEIGHT - 100, 34, 34, 0.12, 100, 100, HPBar_Display::BOUND, sf::Color::Magenta, false);
	this->entity_manager->push(EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Cyborg/cyborg.png", 50 * 32, WINDOW_HEIGHT - 8 * 32 - 20, 32, 34, 0.12, 100, 100, HPBar_Display::BOUND, sf::Color::Blue, false);

	this->current_level = 0;

	try
	{
		int i = 1;
		for (const auto& entry : std::filesystem::directory_iterator(file_manager->maps_directory()))
		{
			if (std::filesystem::is_regular_file(entry) and entry.path().extension() == ".json")
			{
				this->levels.push_back(this->texture_manager->generate_map(entry.path().string(), BACKGROUND + std::to_string(i) + ".png"));
			}
			else {
				throw std::exception("Only .json files!\n");
			}
			i++;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}
}

void Engine::create_entity(std::string entity_texture_path, bool is_playable)
{
	/* #TODO: EntityManager->generate_entity */
}

void Engine::init_view()
{
	view.setSize(WINDOW_LENGTH, WINDOW_HEIGHT);
	view.setCenter(WINDOW_LENGTH / 2, WINDOW_HEIGHT / 2);
}

void Engine::update_view(sf::Vector2f pos)
{
	sf::Vector2f camera = view.getCenter();
	if (pos.x < WINDOW_LENGTH / 2.0f) 
	{ 
		view.setCenter(std::max(pos.x, CURRENT_MAP.x_left_boundary + WINDOW_LENGTH / 2.0f), WINDOW_HEIGHT / 2.0f);
		hero->HPBar->move(camera.x - WINDOW_LENGTH / 2 + 5.0f, 5.0f, true);
	}
	else if (pos.x >= CURRENT_MAP.x_right_boundary - WINDOW_LENGTH / 2.0f) 
	{ 
		view.setCenter(std::min(pos.x, CURRENT_MAP.x_right_boundary - WINDOW_LENGTH / 2.0f), WINDOW_HEIGHT / 2.0f); 
		hero->HPBar->move(camera.x - WINDOW_LENGTH / 2 + 5.0f, 5.0f, true);
	}
	else {
		view.setCenter(pos.x, WINDOW_HEIGHT / 2.0f);
		hero->HPBar->move(camera.x - WINDOW_LENGTH / 2 + 5.0f, 5.0f, true);
	}
}

bool Engine::next_level()
{
	if (current_level + 1 >= levels.size()) { return false; }
	current_level++;
	
	delete entity_manager;
	entity_manager = new EntityManager();

	if (current_level == 1)
	{
		this->entity_manager->push(EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Punk/punk.png", 32 * 26, WINDOW_HEIGHT - 32 * 2.5, 32, 34, 0.12, 100, 100, HPBar_Display::BOUND, sf::Color::Red, false);
		this->entity_manager->push(EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Punk/punk.png", 32 * 3, WINDOW_HEIGHT - 32 * 2.5, 32, 34, 0.0, 100, 100, HPBar_Display::BOUND, sf::Color::Red, false);
	}

	if (current_level == 2)
	{
		this->entity_manager->push(EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Punk/punk.png", 32 * 17, WINDOW_HEIGHT - 32 * 2, 32, 34, 0.0, 100, 100, HPBar_Display::BOUND, sf::Color::Red, false);
		antogonist = this->entity_manager->push(EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Biker/biker.png", 32 * 35, WINDOW_HEIGHT - 32 * 4.5, 32, 34, 0.0, 100, 100, HPBar_Display::BOUND, sf::Color::White, true);
		entity_manager->get_entity(antogonist)->facing_right = false;
	}

	return true;
}

void Engine::check_collisions(float& time)
{
	if (hero->x + hero->width >= CURRENT_MAP.x_right_boundary and next_level()) { 
		hero->change_position(5.0f, 325.0f);
	}
	if (hero->y + hero->height >= CURRENT_MAP.y_bottom_boundary - TILE_SIZE) { 
		hero->take_damage(999999.9f, time); 
	}
	entity_manager->take_damage(entity_manager->check_fell_off(CURRENT_MAP), 999999.f, time);
	hero->collisions(CURRENT_MAP, time);
	entity_manager->check_collison(CURRENT_MAP, time);
}

void Engine::game_loop(sf::RenderWindow& window, float& timer)
{
	if (current_level == 2)
	{
		if (!entity_manager->get_entity(666)->isAlive)
		{
			setGameState(Game_State::FINISH);
		}
	}

	update_view(hero->get_position());
	window.setView(view);

	hero->draw(window);
	hero->draw_hitbox(window);
	hero->draw_health(window);

	entity_manager->draw(window, true, false, false);

	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		hero->take_damage(0.5f, timer);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
	{
		hero->heal(0.5f);
	}

	auto enemy_hit = entity_manager->control(CURRENT_MAP, timer, hero);
	auto hit = hero->control(CURRENT_MAP, timer, nullptr);
	entity_manager->apply_gravity(timer);
	hero->apply_gravity(timer);
	check_collisions(timer);

	entity_manager->take_damage(entity_manager->intersected(hit), DEFAULT_DAMAGE, timer);
	if (hero->intersects(enemy_hit)) { hero->take_damage(DEFAULT_DAMAGE / 2, timer); }

	entity_manager->move(timer);
	hero->move(timer);

	bool deathAnimationPlaying = false;

	if (hero->is_dying())
	{
		deathAnimationPlaying = true;
		hero->play_dying_animation(timer);
	}

	entity_manager->play_dying_animation(entity_manager->is_dying(), timer);

	if (!deathAnimationPlaying)
	{
		if (!hero->isAlive)
		{
			setGameState(Game_State::DEATH);
		}
	}
}

void Engine::menu_loop(sf::RenderWindow& window, float& timer) {
	menu->draw(window, this);
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
			hero->isAlive = true;
			hero->heal(100);
			hero->change_position(32, 325);
			entity_manager->rewrite(0, EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Cyborg/cyborg.png", 32 * 3, WINDOW_HEIGHT - 32 * 2.5, 32, 34, 0.0, 100, 100, HPBar_Display::BOUND, sf::Color::Red);
			entity_manager->rewrite(1, EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Cyborg/cyborg.png", 26 * 32, WINDOW_HEIGHT - 100, 34, 34, 0.12, 100, 100, HPBar_Display::BOUND, sf::Color::Magenta);
			entity_manager->rewrite(2, EntityGroup::NPC, "C:/Users/Home/source/repos/Game/Textures/Character_Textures/Cyborg/cyborg.png", 50 * 32, WINDOW_HEIGHT - 9 * 32, 32, 34, 0.12, 100, 100, HPBar_Display::BOUND, sf::Color::Blue);
			std::cout << "Start button is pressed" << std::endl;
			current_level = 0;
			setGameState(Game_State::GAME);
		}
		if (menu->GetPressedItem() == 1)
		{
			std::cout << "Exit button is pressed" << std::endl;
			window.close();
		}
	}
}

Game_State Engine::getGameState() const {
	return this->gameState;
}

void Engine::setGameState(Game_State state) {
	this->gameState = state;
}

void Engine::map_loop(sf::RenderWindow& window)
{
	CURRENT_MAP.draw_map(window);
}


Engine::~Engine()
{
	delete this->texture_manager, this->hero, this->entity_manager, this->file_manager;
}
