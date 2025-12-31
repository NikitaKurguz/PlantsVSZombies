#include "Zombie.h"

Zombie::Zombie(sf::Vector2f position, float scale_rad, const std::string& file_name, 
	float hp, float velocity, float damage, const sf::IntRect& rect):
	Object(position, scale_rad, file_name, rect), hp(hp), velocity(velocity), damage(damage)
{
	if (TextureManager::GetTextureInstance()->GetTexturePointer(file_name) == nullptr)
		std::cout << "Ошибка загрузки текстуры зомби" << file_name << std::endl;
}

Zombie::~Zombie()
{
}
