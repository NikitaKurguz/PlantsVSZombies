#pragma once
#include "Plant.h"

class Peashooter : public Plant
{
public:
	Peashooter(int row, int col, sf::Vector2f pos, GameField* field);
	void CreateProjectile(Object* target) override;
	Object* FindTargetInRange() override;
};

