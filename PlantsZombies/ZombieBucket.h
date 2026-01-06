#pragma once
#include "Zombie.h"
class ZombieBucket : public Zombie
{
private:
	float bucket_hp;
	float max_bucket_hp = 300;
public:
	ZombieBucket(int row, sf::Vector2f position, GameField* field);
	virtual void SendMessage(Message* m);
	virtual void Update(float t) override;
};

