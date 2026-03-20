#pragma once
#include "Zombie.h"
class ZombieRunner : public Zombie
{
private:
	float armor_hp;
	bool is_tex_ch1, is_tex_ch2;
	float max_armor_hp = 300;
	sf::Texture damaged_tex_1; sf::Texture damaged_tex_2;
public:
	ZombieRunner(int row, sf::Vector2f position, GameField* field);
	void SendMessage(Message* m);
	void Update(float t) override;
	void TakeDmg(float dmg_amount) override;
	void IsDeath() override;
};

