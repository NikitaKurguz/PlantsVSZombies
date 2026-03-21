#include "LevelManager.h"
#include "LawnMower.h"
#include "Peashooter.h"

LevelManager::LevelManager(GameField* field, Manager* manager):
	field(field), manager(manager), max_zombies(1), 
	spawn_delay(5)
{
	for (int row = 0; row < field->get_rows(); ++row)
	{
		sf::Vector2f pos = GetLawnMowerPosition(row);
		LawnMower* mower = new LawnMower(pos, row, field);

		Message* msg = new Message;
		msg->type = MessageType::Create;
		msg->create.new_object = mower;
		manager->SendMessage(msg);
	}
}

void LevelManager::Update(float dt)
{
	if (zombies_spawned >= max_zombies) return;
	spawn_timer += dt;
	if (spawn_timer < spawn_delay) return;

	spawn_timer = 0;

	int row = 3;
	sf::Vector2f spawnPos = GetZombieSpawnPosition(row);

	Zombie* z1 = new Zombie(row, spawnPos, field);

	manager->SendCreateMsg(z1);

	int row_ = rand() % field->get_rows();
	sf::Vector2f spawnPos_ = GetZombieSpawnPosition(row_);
	ZombieBucket* z2 = new ZombieBucket(row_, spawnPos_, field);

	manager->SendCreateMsg(z2);

	int row_r = 1; 
	sf::Vector2f spawnPos_r = GetZombieSpawnPosition(row_r);
	ZombieRunner* z3 = new ZombieRunner(row_r, spawnPos_r, field);

	manager->SendCreateMsg(z3);

	int row_d = 1;
	sf::Vector2f spawnPos_d = GetZombieSpawnPosition(row_d);
	ZombieDancer* z4 = new ZombieDancer(row_d, spawnPos_d, field);

	manager->SendCreateMsg(z4);

	zombies_spawned++;
}

LevelManager::~LevelManager()
{
}
sf::Vector2f LevelManager::GetZombieSpawnPosition(int row) const
{
	return { 1100, field->GetCellCenter(row, 0).y + field->get_cell_size().y * 0.25f};
}
sf::Vector2f LevelManager::GetLawnMowerPosition(int row) const
{
	return {
		field->get_field_origin().x - field->get_cell_size().x * 0.5f,
		field->get_field_origin().y + row * field->get_cell_size().y + field->get_cell_size().y * 0.6f
	};
}

sf::Vector2f LevelManager::GetPlantPosition(int row, int col) const
{
	return { field->GetCellCenter(row, col).x, field->GetCellCenter(row, col).y 
		+ field->get_cell_size().y * 0.2f};
}