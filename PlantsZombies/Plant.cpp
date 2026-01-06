#include"Plant.h"

Plant::Plant(int row, sf::Vector2f position, const std::string& file_name,
    int cost, int range, float hp, float damage, float attackSpeed, float attackTimer,
    const sf::IntRect& rect, sf::Vector2f physical_size,
    GameField* field) :
    Object(position, file_name, rect, physical_size, field), row(row), col(col), cost(cost), range(range), hp(hp),
    attackSpeed(attackSpeed), attackTimer(attackTimer)
{
	CheckTex(file_name);
}

Plant::~Plant()
{

}

void Plant::Update(float t)
{
}

void Plant::CreateProjectile()
{
}

bool Plant::IsCollision(Object* other) const
{
    return false;
}

void Plant::SendMessage(Message* m)
{

}