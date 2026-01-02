#pragma once
#include "GameField.h"
#include "Zombie.h"
#include "Manager.h"
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

};

