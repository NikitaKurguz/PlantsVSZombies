#include "LevelManager.h"

LevelManager::LevelManager(GameField* field, Manager* manager):
	field(field), manager(manager), max_zombies(1), 
	spawn_delay(5)
{

}

void LevelManager::Update(float dt)
{
	srand(time(nullptr));
	if (zombies_spawned >= max_zombies) return;
	spawn_timer += dt;
	if (spawn_timer < spawn_delay) return;

	spawn_timer = 0;

	int row = rand() % 5;

	sf::Vector2f spawnPos = field->GetZombieSpawnPosition(row);
	Zombie* z = new Zombie(row, spawnPos,"textures\\zombies\\DefaultZombie.png",
		100, 4, 10, { 0, 0, 128, 205 }, { 80, 120 });

	Message* msg = new Message;
	msg->type = MessageType::Create;
	msg->create.new_object = z;
	manager->SendMessage(msg);

	zombies_spawned++;
}

LevelManager::~LevelManager()
{
}
