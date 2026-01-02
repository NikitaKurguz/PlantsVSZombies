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
public:
	Zombie(int row, sf::Vector2f position, const std::string& file_name,
		float hp, float velocity, float damage, const sf::IntRect& rect, sf::Vector2f physical_size);
	Zombie();
	virtual ~Zombie();
	int Get_row() const { return row; }
	virtual void SendMessage(Message* m);
	virtual void Update(float t) override;
};

