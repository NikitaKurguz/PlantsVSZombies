#include "Zombie.h"

Zombie::Zombie(sf::Vector2f position, float scale_rad, const sf::Texture& tex, 
	float hp, float velocity, float damage):
	Object(position, scale_rad, tex), hp(hp), velocity(velocity), damage(damage)
{

}

Zombie::~Zombie()
{
}
