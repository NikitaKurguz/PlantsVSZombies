#include "LevelManager.h"
#include "LawnMower.h"

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

	int row = rand() % field->get_rows();
	sf::Vector2f spawnPos = GetZombieSpawnPosition(row);

	Zombie* z1 = new Zombie(row, spawnPos, "textures\\zombies\\DefaultZombie.png",
		100, 4, 20, {0, 0, 128, 205}, {80, 120}, field);

	Message* msg = new Message;
	msg->type = MessageType::Create;
	msg->create.new_object = z1;
	manager->SendMessage(msg);

	int row_ = rand() % field->get_rows();
	sf::Vector2f spawnPos_ = GetZombieSpawnPosition(row_);
	ZombieBucket* z2 = new ZombieBucket(row_, spawnPos_, field);

	Message* msg_ = new Message;
	msg_->type = MessageType::Create;
	msg_->create.new_object = z2;
	manager->SendMessage(msg_);

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