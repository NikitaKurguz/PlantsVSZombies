#pragma once
#include "Object.h"
class Zombie :public Object
{
private:
	float hp;
	float velocity;
	float damage;
public:
	Zombie(sf::Vector2f position, float scale_rad, const sf::Texture& tex,
		float hp, float velocity, float damage);
	virtual ~Zombie();
};

