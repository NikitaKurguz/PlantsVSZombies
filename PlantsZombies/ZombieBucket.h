#pragma once
#include "Zombie.h"
class ZombieBucket : public Zombie
{
private:
	float bucket_hp;
	float max_bucket_hp = 100;
	bool is_tex_changed = false;
	sf::Texture damaged_tex;
public:
	ZombieBucket(int row, sf::Vector2f position, GameField* field);
	void SendMessage(Message* m);
	void Update(float t) override;
	void TakeDmg(float dmg_amount) override;
	void IsDeath() override;
};

