#pragma once
#include "Object.h"
#include <string>
#include <iostream>
class Zombie : public Object
{
protected:
	float hp;
	float velocity;
	float damage;
public:
	Zombie(sf::Vector2f position, const std::string& file_name,
		float hp, float velocity, float damage, const sf::IntRect& rect);
	Zombie();
	virtual ~Zombie();
	virtual void SendMessage(Message* m);
	virtual void Update(float t);
};

