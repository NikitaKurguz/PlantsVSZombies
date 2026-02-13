#pragma once
#include "Plant.h"
class Peashooter : public Plant
{
private:
	
public:
	Peashooter(int row, int col, sf::Vector2f pos, GameField* field);
	~Peashooter();

	void SendMessage(Message* m) override;
	void Update(float t) override;
	void CreateProjectile(Object* target) override;
	Object* FindTargetInRange() override;

};

