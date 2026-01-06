#pragma once
#include "Object.h"
#include <string>
#include <iostream>
class Zombie : public Object
{
protected:
	int row;
	float hp;
	float velocity;
	float damage;
	float attack_speed;
	float attack_timer = 0;

	bool isAttacking = false;
	Object* target = nullptr;
	void IsDeath();
	virtual void Move(float t);
public:
	Zombie(int row, sf::Vector2f position, const std::string& file_name,
		float hp, float velocity, float damage, const sf::IntRect& rect, sf::Vector2f physical_size, float attack_speed,
		GameField* field);
	virtual ~Zombie();
	int Get_row() const override { return row; }
	float Get_hp() const { return hp; }
	CollisionObject GetType() const override { return CollisionObject::Zombie; }
	bool IsCollision(Object* other) const override;
	virtual void TakeDmg(float dmg_amount);
	virtual void StartAttack(Object* plant);
	virtual void StopAttack();
	void SendAttackToObject();
	
	virtual void SendMessage(Message* m);
	virtual void Update(float t) override;
};

