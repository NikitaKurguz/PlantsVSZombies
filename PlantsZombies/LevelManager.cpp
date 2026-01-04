#include "LevelManager.h"
#include "LawnMower.h"

LevelManager::LevelManager(GameField* field, Manager* manager):
	field(field), manager(manager), max_zombies(1), 
	spawn_delay(5)
{
	for (int row = 0; row < field->get_rows(); ++row)
	{
		sf::Vector2f pos = field->GetLawnMowerPosition(row);
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
	sf::Vector2f spawnPos = field->GetZombieSpawnPosition(row);
	Zombie* z = new Zombie(row, spawnPos,"textures\\zombies\\DefaultZombie.png",
		100, 10, 10, { 0, 0, 128, 205 }, { 80, 120 }, field);

	Message* msg = new Message;
	msg->type = MessageType::Create;
	msg->create.new_object = z;
	manager->SendMessage(msg);

	zombies_spawned++;
}

LevelManager::~LevelManager()
{
}
