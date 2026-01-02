#include "Zombie.h"
#include "GameField.h"

Zombie::Zombie(int row, sf::Vector2f position, const std::string& file_name, 
	float hp, float velocity, float damage, const sf::IntRect& rect, sf::Vector2f physical_size):
	Object(position, file_name, rect, physical_size), hp(hp), velocity(velocity), damage(damage), row(row)
{
	CheckTex(file_name);
}

Zombie::~Zombie()
{
}



void Zombie::SendMessage(Message* m)
{
}

void Zombie::Update(float t)
{
	position.x -= t * velocity;
}


