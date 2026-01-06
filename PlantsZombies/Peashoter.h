#pragma once
#include "Plant.h"
class Peashoter : public Plant
{
private:
	
public:
	Peashoter(int row, int col, sf::Vector2f pos, GameField* field);
	~Peashoter();

	void SendMessage(Message* m) override;
	void Update(float t) override;
	void CreateProjectile() override;
};

