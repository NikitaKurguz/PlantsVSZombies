#pragma once
#include "Object.h"
#include <iostream>
class Zombie :public Object
{
protected:
	float hp;
	float velocity;
	float damage;
public:
	Zombie(sf::Vector2f position, float scale_rad, const std::string& file_name,
		float hp, float velocity, float damage);
	virtual ~Zombie();
};

