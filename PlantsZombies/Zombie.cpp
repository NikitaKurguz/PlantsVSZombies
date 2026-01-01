#include "Zombie.h"

Zombie::Zombie(sf::Vector2f position, const std::string& file_name, 
	float hp, float velocity, float damage, const sf::IntRect& rect):
	Object(position, file_name, rect), hp(hp), velocity(velocity), damage(damage)
{
	CheckTex(file_name);
}

Zombie::Zombie():
	Object(sf::Vector2f(0, 0), "default_zombie.png", sf::IntRect(0, 0, 32, 32)),
	hp(100), velocity(2), damage(10)
{
	CheckTex("default_zombie.png");
}


Zombie::~Zombie()
{
}



void Zombie::SendMessage(Message* m)
{
}

void Zombie::Update(float t)
{
}


