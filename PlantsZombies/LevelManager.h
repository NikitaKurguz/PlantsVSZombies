#pragma once
#include "GameField.h"
#include "Zombie.h"
#include "ZombieBucket.h"
#include "Manager.h"
class Plant;
class LevelManager
{
private:
	GameField* field;
	Manager* manager;

	int max_zombies;
	int zombies_spawned = 0;
	float spawn_timer = 0;
	float spawn_delay;
public:
	LevelManager(GameField* field, Manager* manager);
	void Update(float dt);
	~LevelManager();
	sf::Vector2f GetZombieSpawnPosition(int row) const;
	sf::Vector2f GetLawnMowerPosition(int row) const;
	sf::Vector2f GetPlantPosition(int row, int col) const;
};

